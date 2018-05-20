#include <stdlib.h>
#include <stdio.h>
#include "myassert.h"
#include "diff.h"

#define EPSILON 1e-3

int main() {
    labcolor c1, c2;

    labcolor_init(&c1, 50.0f, 2.6772f, -79.7751f);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true chroma difference (#1)", 2.0425f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 3.1571f, -77.2803);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true chroma difference (#2)", 2.8615f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.8361f, -74.0200f);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true chroma difference (#3)", 3.4412f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -1.3802f, -84.2814f);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true hue difference (#4)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -1.1848f, -84.8006f);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true hue difference (#5)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -0.9009f, -85.5211f);
    labcolor_init(&c2, 50.0f, 0.0000f, -82.7485f);
    assertEqualsFloat("should use the true hue difference (#6)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 0.0000f, 0.0000f);
    labcolor_init(&c2, 50.0f, -1.0000f, 2.0000f);
    assertEqualsFloat("should use the correct arctangent computation (#7)", 2.3669f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -1.0000f, 2.0000f);
    labcolor_init(&c2, 50.0f, 0.0000f, 0.0000f);
    assertEqualsFloat("should use the correct arctangent computation (#8)", 2.3669f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.4900f, -0.0010f);
    labcolor_init(&c2, 50.0f, -2.4900f, 0.0009f);
    assertEqualsFloat("should use the correct arctangent computation (#9)", 7.1792f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.4900f, -0.0010f);
    labcolor_init(&c2, 50.0f, -2.4900, 0.0010f);
    assertEqualsFloat("should use the correct arctangent computation (#10)", 7.1792f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.4900f, -0.0010f);
    labcolor_init(&c2, 50.0f, -2.4900f, 0.0011f);
    assertEqualsFloat("should use the correct arctangent computation (#11)", 7.2195f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.4900f, -0.0010f);
    labcolor_init(&c2, 50.0f, -2.4900f, 0.0012f);
    assertEqualsFloat("should use the correct arctangent computation (#12)", 7.2195f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -0.0010f, 2.4900f);
    labcolor_init(&c2, 50.0f, 0.0009f, -2.4900f);
    assertEqualsFloat("should use the correct arctangent computation (#13)", 4.8045f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -0.0010f, 2.4900f);
    labcolor_init(&c2, 50.0f, 0.0010f, -2.4900f);
    assertEqualsFloat("should use the correct arctangent computation (#14)", 4.8045f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, -0.0010f, 2.4900f);
    labcolor_init(&c2, 50.0f, 0.0011f, -2.4900f);
    assertEqualsFloat("should use the correct arctangent computation (#15)", 4.7461f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 50.0f, 0.0000f, -2.5000f);
    assertEqualsFloat("should use the correct arctangent computation (#16)", 4.3065f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 73.0000f, 25.0000f, -18.0000f);
    assertEqualsFloat("should work for large color differences (#17)", 27.1492f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 61.0000f, -5.0000f, 29.0000f);
    assertEqualsFloat("should work for large color differences (#18)", 22.8977f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 56.0000, -27.0000f, -3.0000f);
    assertEqualsFloat("should work for large color differences (#19)", 31.9030f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 58.0000f, 24.0000f, 15.0000f);
    assertEqualsFloat("should work for large color differences (#20)", 19.4535f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0000f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 50.0000f, 3.1736f, 0.5854f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#21)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 50.0f, 3.2972f, 0.0000f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#22)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 50.0f, 1.8634f, 0.5757f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#23)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 50.0f, 2.5000f, 0.0000f);
    labcolor_init(&c2, 50.0f, 3.2592f, 0.3350f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#24)", 1.0000f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 60.2574f, -34.0099f, 36.2677f);
    labcolor_init(&c2, 60.4626f, -34.1751f, 39.4387f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#25)", 1.2644f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 63.0109f, -31.0961f, -5.8663f);
    labcolor_init(&c2, 62.8187f, -29.7946f, -4.0864f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#26)", 1.2630f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 61.2901f, 3.7196f, -5.3901f);
    labcolor_init(&c2, 61.4292f, 2.2480f, -4.9620f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#27)", 1.8731f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 35.0831f, -44.1164f, 3.7933f);
    labcolor_init(&c2, 35.0232f, -40.0716f, 1.5901f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#28)", 1.8645f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 22.7233f, 20.0904f, -46.6940f);
    labcolor_init(&c2, 23.0331f, 14.9730f, -42.5619f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#29)", 2.0373f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 36.4612f, 47.8580f, 18.3852f);
    labcolor_init(&c2, 36.2715f, 50.5065f, 21.2231f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#30)", 1.4146f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 90.8027f, -2.0831f, 1.4410f);
    labcolor_init(&c2, 91.1528f, -1.6435f, 0.0447f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#31)", 1.4441f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 90.9257f, -0.5406f, -0.9208f);
    labcolor_init(&c2, 88.6381f, -0.8985f, -0.7239f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#32)", 1.5381f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 6.7747f, -0.2908f, -2.4247f);
    labcolor_init(&c2, 5.8714f, -0.0985f, -2.2286f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#33)", 0.6377f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 2.0776f, 0.0795f, -1.1350f);
    labcolor_init(&c2, 0.9033f, -0.0636f, -0.5514f);
    assertEqualsFloat("should produce numbers found in the CIE technical report (#34)", 0.9082f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 100.0f, 0.005f, -0.010f);
    labcolor_init(&c2, 100.0f, 0.005f, -0.010f);
    assertEqualsFloat("Same color should have 0.0 difference #1", 0.0f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 0.0f, 0.0f, 0.0f);
    labcolor_init(&c2, 0.0f, 0.0f, 0.0f);
    assertEqualsFloat("Same color should have 0.0 difference #2", 0.0f, ciede2000(&c1, &c2), EPSILON);

    labcolor_init(&c1, 100.0f, 0.005f, -0.010f);
    labcolor_init(&c2, 0.0f, 0.0f, 0.0f);
    assertEqualsFloat("Black and white are very different", 100.0f, ciede2000(&c1, &c2), EPSILON);

    printf("All tests passed!\n");
    
    return EXIT_SUCCESS;
}
