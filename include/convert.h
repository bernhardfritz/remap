#ifndef CONVERT_H
#define CONVERT_H

#include "color.h"

void rgb_to_lab(rgbcolor* rgb, labcolor* lab);
void rgba_to_rgb(rgbacolor* rgba, rgbcolor* rgb, rgbcolor* bg);
void rgba_to_lab(rgbacolor* rgba, labcolor* lab, rgbcolor* bg);

#endif /* CONVERT_H */
