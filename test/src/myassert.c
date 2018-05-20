#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "myassert.h"

void assertEqualsFloat(const char* message, float expected, float actual, float epsilon) {
    if (fabsf(expected - actual) >= epsilon) {
        fprintf(stderr, "Test failed! %s: %.2f is expected to be equal to %.2f\n", message, actual, expected);
        exit(EXIT_FAILURE);
    }
}

void assertEqualsLabcolor(const char* message, labcolor* expected, labcolor* actual, float epsilon) {
    assertEqualsFloat(message, expected->L, actual->L, epsilon);
    assertEqualsFloat(message, expected->a, actual->a, epsilon);
    assertEqualsFloat(message, expected->b, actual->b, epsilon);
}
