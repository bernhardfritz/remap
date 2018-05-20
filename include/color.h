#ifndef COLOR_H
#define COLOR_H

typedef struct {
    float R, G, B;
} rgbcolor;

typedef struct {
    float R, G, B, A;
} rgbacolor;

typedef struct {
    float X, Y, Z;
} xyzcolor;

typedef struct {
    float L, a, b;
} labcolor;

void rgbcolor_init(rgbcolor* rgb, float R, float G, float B);
void rgbacolor_init(rgbacolor* rgba, float R, float G, float B, float A);
void xyzcolor_init(xyzcolor* xyz, float X, float Y, float Z);
void labcolor_init(labcolor* lab, float L, float a, float b);

#endif /* COLOR_H */
