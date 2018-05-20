#ifndef MYASSERT_H
#define MYASSERT_H

#include "color.h"

void assertEqualsFloat(const char* message, float expected, float actual, float epsilon);
void assertEqualsLabcolor(const char* message, labcolor* expected, labcolor* actual, float epsilon);

#endif /* MYASSERT_H */
