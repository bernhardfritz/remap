#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
#include "diff.h"

float degrees(float n) {
    return n * (180.0f / M_PI);
}

float radians(float n) {
    return n * (M_PI / 180.0f);
}

float hp_f(float x, float y) {
    if (x == 0.0f && y == 0.0f) {
        return 0.0f;
    } else {
        float tmphp = degrees(atan2f(x, y));
        if (tmphp >= 0.0f) {
            return tmphp;
        } else {
            return tmphp + 360.0f;
        }
    }
}

float dhp_f(float C1, float C2, float h1p, float h2p) {
    if (C1 * C2 == 0.0f) {
        return 0.0f;
    } else if(fabsf(h2p - h1p) <= 180.0f) {
        return h2p - h1p;
    } else if((h2p - h1p) > 180.0f) {
        return (h2p - h1p) - 360.0f;
    } else if((h2p - h1p) < -180.0f) {
        return (h2p - h1p) + 360.0f;
    } else {
        exit(EXIT_FAILURE);
    }
}

float a_hp_f(float C1, float C2, float h1p, float h2p) {
    if (C1 * C2 == 0.0f) {
        return h1p + h2p;
    } else if(fabsf(h1p - h2p) <= 180.0f) {
        return (h1p + h2p) / 2.0f;
    } else if((fabsf(h1p - h2p) > 180.0f) && ((h1p + h2p) < 360.0f)) {
        return (h1p + h2p + 360.0f) / 2.0f;
    } else if((fabsf(h1p - h2p) > 180.0f) && ((h1p + h2p) >= 360.0f)) {
        return (h1p + h2p - 360.0f) / 2.0f;
    } else {
        exit(EXIT_FAILURE);
    }
}

float ciede2000(labcolor* c1, labcolor* c2) {
    float L1 = c1->L;
    float a1 = c1->a;
    float b1 = c1->b;

    float L2 = c2->L;
    float a2 = c2->a;
    float b2 = c2->b;

    float kL = 1.0f;
    float kC = 1.0f;
    float kH = 1.0f;

    float C1 = sqrtf(powf(a1, 2.0f) + powf(b1, 2.0f));
    float C2 = sqrtf(powf(a2, 2.0f) + powf(b2, 2.0f));

    float a_C1_C2 = (C1 + C2) / 2.0f;

    float G = 0.5f * (1.0f - sqrtf(powf(a_C1_C2, 7.0f) / (powf(a_C1_C2, 7.0f) + powf(25.0f, 7.0f))));

    float a1p = (1.0f + G) * a1;
    float a2p = (1.0f + G) * a2;

    float C1p = sqrtf(powf(a1p, 2.0f) + powf(b1, 2.0f));
    float C2p = sqrtf(powf(a2p, 2.0f) + powf(b2, 2.0f));

    float h1p = hp_f(b1, a1p);
    float h2p = hp_f(b2, a2p);

    float dLp = L2 - L1;
    float dCp = C2p - C1p;

    float dhp = dhp_f(C1, C2, h1p, h2p);
    float dHp = 2 * sqrtf(C1p * C2p) * sinf(radians(dhp) / 2.0f);

    float a_L = (L1 + L2) / 2.0f;
    float a_Cp = (C1p + C2p) / 2.0f;

    float a_hp = a_hp_f(C1, C2, h1p, h2p);
    float T = 1.0f - 0.17f * cosf(radians(a_hp - 30.0f)) + 0.24f * cosf(radians(2.0f * a_hp)) + 0.32f * cosf(radians(3.0f * a_hp + 6.0f)) - 0.20f * cosf(radians(4.0f * a_hp - 63.0f));
    float d_ro = 30.0f * expf(-(powf((a_hp - 275.0f) / 25.0f, 2.0f)));
    float RC = sqrtf((powf(a_Cp, 7.0f)) / (powf(a_Cp, 7.0f) + powf(25.0f, 7.0f)));
    float SL = 1.0f + ((0.015f * powf(a_L - 50.0f, 2.0f)) / sqrtf(20.0f + powf(a_L - 50.0f, 2.0f)));
    float SC = 1.0f + 0.045f * a_Cp;
    float SH = 1.0f + 0.015f * a_Cp * T;
    float RT = -2.0f * RC * sinf(radians(2.0f * d_ro));
    float dE = sqrtf(powf(dLp / (SL * kL), 2.0f) + powf(dCp / (SC * kC), 2.0f) + powf(dHp / (SH * kH), 2.0f) + RT * (dCp / (SC * kC)) * (dHp / (SH * kH)));
    return dE;
}
