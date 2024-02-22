#include <stdio.h>
#include <stdlib.h>
#define VEC_TYPE float
#include "linear_algebra.h"

int main(void)
{
	Vec2 a = (Vec2) { .a_0 = 4.0, .a_1 = 2.0 };
	Vec2 b = (Vec2) { .a_0 = 1.0, .a_1 = 1.0 };
	Mat4x2 m = (Mat4x2) {
		.a_0 = (Vec4) { .a_0 = 2.0, .a_1 = 3.0, .a_2 = 4.0, .a_3 = 4.0 },
		.a_1 = (Vec4) { .a_0 = 2.0, .a_1 = 3.0, .a_2 = 4.0, .a_3 = 4.0 },
	};
	Vec2 c = vec2_add(a, b);
	Vec4 d = mat4x2_vec2_mult(m, a);
	printf("a0 %f, a1 %f\n", c.a_0, c.a_1);
	printf("a0 %f, a1 %f, a2 %f, a3 %f\n", d.a_0, d.a_1, d.a_2, d.a_3);
	return 0;
}
