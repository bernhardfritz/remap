#include <stdlib.h>
#include <stdio.h>
#include "myassert.h"
#include "convert.h"

#define EPSILON 1e-3

int main() {
    rgbcolor rgb;
    rgbacolor rgba;
    labcolor expected, actual;

    rgbcolor_init(&rgb, 55.0f, 100.0f, 130.0f);
    rgb_to_lab(&rgb, &actual);
    labcolor_init(&expected, 40.473f, -6.106f, -21.417f);
    assertEqualsLabcolor("should convert to expected lab color #1", &expected, &actual, EPSILON);

    rgbcolor_init(&rgb, 0.0f, 0.0f, 0.0f);
    rgb_to_lab(&rgb, &actual);
    labcolor_init(&expected, 0.0f, 0.0f, 0.0f);
    assertEqualsLabcolor("should convert to expected lab color #2", &expected, &actual, EPSILON);

    rgbcolor_init(&rgb, 255.0f, 255.0f, 255.0f);
    rgb_to_lab(&rgb, &actual);
    labcolor_init(&expected, 100.0f, 0.005f, -0.010f);
    assertEqualsLabcolor("should convert to expected lab color #3", &expected, &actual, EPSILON);

    rgbacolor_init(&rgba, 0.0f, 0.0f, 0.0f, 0.0f);
    rgba_to_lab(&rgba, &actual, NULL);
    labcolor_init(&expected, 100.0f, 0.005f, -0.010f);
    assertEqualsLabcolor("should convert to expected lab color #4", &expected, &actual, EPSILON);

    rgbacolor_init(&rgba, 0.0f, 0.0f, 0.0f, 0.0f);
    rgba_to_lab(&rgba, &actual, NULL);
    labcolor_init(&expected, 100.0f, 0.005f, -0.010f);
    assertEqualsLabcolor("should convert to expected lab color #5", &expected, &actual, EPSILON);

    rgbacolor_init(&rgba, 0.0f, 0.0f, 0.0f, 0.5f);
    rgba_to_lab(&rgba, &actual, NULL);
    labcolor_init(&expected, 53.389f, 0.003f, -0.006f);
    assertEqualsLabcolor("should convert to expected lab color #6", &expected, &actual, EPSILON);

    printf("All tests passed!\n");

    return EXIT_SUCCESS;
}
