#include <stdlib.h>
#include <math.h>
#include "color.h"

void rgb_to_xyz(rgbcolor* rgb, xyzcolor* xyz) {
    // Based on http://www.easyrgb.com/index.php?X=MATH&H=02
    float R = (rgb->R / 255.0f);
    float G = (rgb->G / 255.0f);
    float B = (rgb->B / 255.0f);

    if (R > 0.04045f) {
        R = powf(((R + 0.055f) / 1.055f), 2.4f);
    } else {
        R = R / 12.92f;
    }
    if (G > 0.04045f) {
        G = powf(((G + 0.055f) / 1.055f), 2.4f);
    } else {
        G = G / 12.92f;
    }
    if (B > 0.04045f) {
        B = powf(((B + 0.055f) / 1.055f), 2.4f);
    } else {
        B = B / 12.92f;
    }

  R *= 100.0f;
  G *= 100.0f;
  B *= 100.0f;

  // Observer. = 2°, Illuminant = D65
  float X = R * 0.4124f + G * 0.3576f + B * 0.1805f;
  float Y = R * 0.2126f + G * 0.7152f + B * 0.0722f;
  float Z = R * 0.0193f + G * 0.1192f + B * 0.9505f;

  xyzcolor_init(xyz, X, Y, Z);
}

void xyz_to_lab(xyzcolor* xyz, labcolor* lab) {
    // Based on http://www.easyrgb.com/index.php?X=MATH&H=07
    float ref_Y = 100.000f;
    float ref_Z = 108.883f;
    float ref_X = 95.047f; // Observer= 2°, Illuminant= D65
    float Y = xyz->Y / ref_Y;
    float Z = xyz->Z / ref_Z;
    float X = xyz->X / ref_X;
    if (X > 0.008856f) {
        X = powf(X, 1.0f / 3.0f);
    } else {
        X = (7.787f * X) + (16.0f / 116.0f);
    }
    if (Y > 0.008856f) {
        Y = powf(Y, 1.0f / 3.0f);
    } else {
        Y = (7.787f * Y) + (16.0f / 116.0f);
    }
    if (Z > 0.008856f) {
        Z = powf(Z, 1.0f / 3.0f);
    } else {
        Z = (7.787f * Z) + (16.0f / 116.0f);
    }
    float L = (116.0f * Y) - 16.0f;
    float a = 500.0f * (X - Y);
    float b = 200.0f * (Y - Z);

    labcolor_init(lab, L, a, b);
}

void rgb_to_lab(rgbcolor* rgb, labcolor* lab) {
    xyzcolor xyz;
    rgb_to_xyz(rgb, &xyz);
    xyz_to_lab(&xyz, lab);
}

void rgba_to_rgb(rgbacolor* rgba, rgbcolor* rgb, rgbcolor* bg) {
    rgbcolor tmp;
    rgbcolor_init(&tmp, bg ? bg->R : 255.0f, bg ? bg->G : 255.0f, bg ? bg->B : 255.0f);
    float R = tmp.R + (rgba->R - tmp.R) * rgba->A;
    float G = tmp.G + (rgba->G - tmp.G) * rgba->A;
    float B = tmp.B + (rgba->B - tmp.B) * rgba->A;

    rgbcolor_init(rgb, R, G, B);
}

void rgba_to_lab(rgbacolor* rgba, labcolor* lab, rgbcolor* bc) {
    rgbcolor rgb;
    rgba_to_rgb(rgba, &rgb, bc);
    rgb_to_lab(&rgb, lab);
}
