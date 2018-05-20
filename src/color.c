#include "color.h"

void rgbcolor_init(rgbcolor* rgb, float R, float G, float B) {
    rgb->R = R;
    rgb->G = G;
    rgb->B = B;
}

void rgbacolor_init(rgbacolor* rgba, float R, float G, float B, float A) {
    rgba->R = R;
    rgba->G = G;
    rgba->B = B;
    rgba->A = A;
}

void xyzcolor_init(xyzcolor* xyz, float X, float Y, float Z) {
    xyz->X = X;
    xyz->Y = Y;
    xyz->Z = Z;
}

void labcolor_init(labcolor* lab, float L, float a, float b) {
    lab->L = L;
    lab->a = a;
    lab->b = b;
}
