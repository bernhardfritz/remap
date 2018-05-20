#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "convert.h"
#include "diff.h"

const char* get_filename_ext(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return "";
    }
    return dot + 1;
}

int perfectHashRgbcolor(const void* key) {
    rgbcolor* rgb = (rgbcolor*) key;
	unsigned char R = (unsigned char) rgb->R;
    unsigned char G = (unsigned char) rgb->G;
    unsigned char B = (unsigned char) rgb->B;
	return ((R & 0xff) << 16) + ((G & 0xff) << 8) + (B & 0xff);
}

int compareRgbcolor(const void* a, const void* b) {
    rgbcolor* rgb1 = (rgbcolor*) a;
    rgbcolor* rgb2 = (rgbcolor*) b;
    return perfectHashRgbcolor(rgb1) - perfectHashRgbcolor(rgb2);
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s inputFilename paletteFilename outputFilename\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* inputFilename = argv[1];
	if (access(inputFilename, F_OK) == -1) {
		fprintf(stderr, "%s cannot be found\n", inputFilename);
		return EXIT_FAILURE;
	}
    char* paletteFilename = argv[2];
	if (access(paletteFilename, F_OK) == -1) {
		fprintf(stderr, "%s cannot be found\n", paletteFilename);
		return EXIT_FAILURE;
	}
    char* outputFilename = argv[3];
	const char* outputFileExtension = get_filename_ext(outputFilename);

    int inputWidth, inputHeight, inputFormat;
    unsigned char* inputImage = stbi_load(inputFilename, &inputWidth, &inputHeight, &inputFormat, 0);

    int paletteWidth, paletteHeight, paletteFormat;
    unsigned char* paletteImage = stbi_load(paletteFilename, &paletteWidth, &paletteHeight, &paletteFormat, 0);

    rgbcolor rgbPaletteColors[paletteWidth * paletteHeight];

    for (int i = 0; i < paletteWidth * paletteHeight; i++) {
        float R = (float) paletteImage[i * paletteFormat + 0];
        float G = (float) paletteImage[i * paletteFormat + 1];
        float B = (float) paletteImage[i * paletteFormat + 2];

        if (paletteFormat == 4) {
            float A = (float) paletteImage[i * paletteFormat + 3] / 255.0f;
            rgbacolor rgba;
            rgbacolor_init(&rgba, R, G, B, A);
            rgbcolor rgb;
            rgba_to_rgb(&rgba, &rgb, NULL);
            R = rgb.R;
            G = rgb.G;
            B = rgb.B;
        }
        
        rgbcolor_init(rgbPaletteColors + i, R, G, B);
    }

    qsort(rgbPaletteColors, paletteWidth * paletteHeight, sizeof(rgbcolor), compareRgbcolor);

    rgbcolor uniqueRgbPaletteColors[paletteWidth * paletteHeight];
    int countOfUniquePaletteColors = 0;
    for (int i = 0; i < paletteWidth * paletteHeight; i++) {
        rgbcolor* rgbPaletteColor = rgbPaletteColors + i;
        float R = rgbPaletteColor->R;
        float G = rgbPaletteColor->G;
        float B = rgbPaletteColor->B;
        if (i == 0) {
            rgbcolor_init(uniqueRgbPaletteColors + countOfUniquePaletteColors++, R, G, B);
        } else {
            rgbcolor* lastUniqueRgbPaletteColor = uniqueRgbPaletteColors + countOfUniquePaletteColors - 1;
            if (R != lastUniqueRgbPaletteColor->R || G != lastUniqueRgbPaletteColor->G || B != lastUniqueRgbPaletteColor->B) {
                rgbcolor_init(uniqueRgbPaletteColors + countOfUniquePaletteColors++, R, G, B);
            }
        }
    }

    labcolor uniqueLabPaletteColors[countOfUniquePaletteColors];
    for (int i = 0; i < countOfUniquePaletteColors; i++) {
        rgb_to_lab(uniqueRgbPaletteColors + i, uniqueLabPaletteColors + i);
    }

    unsigned char* outputImage = (unsigned char*) malloc(inputWidth * inputHeight * inputFormat * sizeof(unsigned char));
    if (!outputImage) {
        perror("Failed to allocate memory for outputImage");
        return EXIT_FAILURE;
    }

    rgbcolor** remap = calloc(256 * 256 * 256, sizeof(rgbcolor*));
    if (!remap) {
        perror("Failed to allocate memory for remap");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < inputWidth * inputHeight; i++) {
        float R = (float) inputImage[i * inputFormat + 0];
        float G = (float) inputImage[i * inputFormat + 1];
        float B = (float) inputImage[i * inputFormat + 2];

        if (inputFormat == 4) {
            float A = (float) inputImage[i * inputFormat + 3] / 255.0f;
            if (A == 0.0f) {
                outputImage[i * inputFormat + 3] = inputImage[i * inputFormat + 3];
                continue;
            }
            rgbacolor rgba;
            rgbacolor_init(&rgba, R, G, B, A);
            rgbcolor rgb;
            rgba_to_rgb(&rgba, &rgb, NULL);
            R = rgb.R;
            G = rgb.G;
            B = rgb.B;
        }

        rgbcolor rgb;
        rgbcolor_init(&rgb, R, G, B);

        rgbcolor* bestFittingPaletteColor = remap[perfectHashRgbcolor(&rgb)];

        if (!bestFittingPaletteColor) {
            labcolor lab;        
            rgb_to_lab(&rgb, &lab);
            float minDiff = 100.0f;
            int indexOfBestFittingPaletteColor = 0;
            for (int i = 0; i < countOfUniquePaletteColors; i++) {
                float diff = ciede2000(&lab, uniqueLabPaletteColors + i);
                if (diff < minDiff) {
                    minDiff = diff;
                    indexOfBestFittingPaletteColor = i;
                }
            }
            bestFittingPaletteColor = uniqueRgbPaletteColors + indexOfBestFittingPaletteColor;
            remap[perfectHashRgbcolor(&rgb)] = bestFittingPaletteColor;
        }

        outputImage[i * inputFormat + 0] = (unsigned char) bestFittingPaletteColor->R;
        outputImage[i * inputFormat + 1] = (unsigned char) bestFittingPaletteColor->G;
        outputImage[i * inputFormat + 2] = (unsigned char) bestFittingPaletteColor->B;
        if (inputFormat == 4) {
            outputImage[i * inputFormat + 3] = (unsigned char) 255;
        }
    }

    free(remap);

    int success = 0;
	if (strcmp(outputFileExtension, "png") == 0) {
		success = stbi_write_png(outputFilename, inputWidth, inputHeight, inputFormat, outputImage, 0);
	} else if (strcmp(outputFileExtension, "bmp") == 0) {
		success = stbi_write_bmp(outputFilename, inputWidth, inputHeight, inputFormat, outputImage);
	} else if (strcmp(outputFileExtension, "tga") == 0) {
		success = stbi_write_tga(outputFilename, inputWidth, inputHeight, inputFormat, outputImage);
	} else if (strcmp(outputFileExtension, "jpg") == 0) {
		success = stbi_write_jpg(outputFilename, inputWidth, inputHeight, inputFormat, outputImage, 100);
	} else {
		fprintf(stderr, "The file extension \"%s\" is not supported. Please use one of the following instead: png, bmp, tga, jpg\n", outputFileExtension);
	}
	if (!success) {
		fprintf(stderr, "Unable to write %s\n", outputFilename);
	}

    stbi_image_free(inputImage);
    stbi_image_free(paletteImage);
    free(outputImage);

    return EXIT_SUCCESS;
}
