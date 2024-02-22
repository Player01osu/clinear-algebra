#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void write_header(FILE *f)
{
	const char HEADER[] = "#ifndef VEC_TYPE\n"
		"#error Define a type with \"VEC_TYPE\"\n"
		"#else\n"
		"#define T VEC_TYPE\n"
		"#endif\n";
	fwrite(HEADER, sizeof(HEADER) - 1, sizeof(char), f);
}

size_t radix_n(size_t n)
{
	size_t a = 0;
	while (n > 0) {
		n = n / 10;
		++a;
	}
	return a;
}

void write_vec_struct_def(FILE *f, size_t dimension)
{
	fprintf(f, "typedef struct {\n");
	for (size_t i = 0; i < dimension; ++i) {
		fprintf(f, "\tT a_%ld;\n", i);
	}

	fprintf(f, "} Vec%ld;\n", dimension);
}

void write_vec_add_func(FILE *f, size_t dimension)
{
	fprintf(f, "Vec%ld vec%ld_add(Vec%ld a_1, Vec%ld a_2)\n"
		"{\n"
		"\treturn (Vec%ld) {\n",
		dimension, dimension, dimension,
		dimension, dimension);

	for (size_t i = 0; i < dimension; ++i) {
		fprintf(f, "\t\t.a_%ld = a_1.a_%ld + a_2.a_%ld,\n", i, i, i);
	}
	fprintf(f, "\t};\n""}\n");

}

void write_vec_scale_func(FILE *f, size_t dimension)
{
	fprintf(f, "Vec%ld vec%ld_scale(Vec%ld a_1, T scalar)\n"
		"{\n"
		"\treturn (Vec%ld) {\n",
		dimension, dimension, dimension, dimension);

	for (size_t i = 0; i < dimension; ++i) {
		fprintf(f, "\t\t.a_%ld = a_1.a_%ld * scalar,\n", i, i);
	}
	fprintf(f, "\t};\n""}\n");

}

void write_vec_dot_func(FILE *f, size_t dimension)
{
	fprintf(f, "T vec%ld_dot(Vec%ld a_1, Vec%ld a_2)\n{\n",
		dimension, dimension, dimension);

	for (size_t i = 0; i < dimension; ++i) {
		if (i == 0) {
			fprintf(f, "\treturn a_1.a_%ld * a_2.a_%ld", i, i);
			continue;
		}
		fprintf(f, " + a_1.a_%ld * a_2.a_%ld", i, i);
	}
	fprintf(f, ";\n""}\n");
}

void write_mat_struct_def(FILE *f, size_t rows, size_t cols)
{
	fprintf(f, "typedef struct {\n");
	for (size_t i = 0; i < cols; ++i) {
		fprintf(f, "\tVec%ld a_%ld;\n", rows, i);
	}

	fprintf(f, "} Mat%ldx%ld;\n", rows, cols);
}

void write_mat_vec_mult_func(FILE *f, size_t rows, size_t cols)
{
	fprintf(f, "Vec%ld mat%ldx%ld_vec%ld_mult(Mat%ldx%ld m, Vec%ld a)\n"
		"{\n",
		rows, rows, cols, cols,
		rows, cols, cols);

	fprintf(f, "\treturn (Vec%ld) {\n", rows);
	for (size_t row = 0; row < rows; ++row) {
		fprintf(f, "\t\t.a_%ld = vec%ld_dot((Vec%ld) {", row, cols, cols);
		for (size_t col = 0; col < cols; ++col) {
			fprintf(f, ".a_%ld = m.a_%ld.a_%ld,", col, col, row);
		}
		fprintf(f, "}, a),\n");
	}
	fprintf(f, "\t};\n""}\n");
}

void write_vec_structs(FILE *f, size_t min_d, size_t max_d, bool write_mat)
{
	for (size_t d = min_d; d <= max_d; ++d) {
		write_vec_struct_def(f, d);
	}

	if (write_mat) {
		for (size_t rows = min_d; rows <= max_d; ++rows) {
			for (size_t cols = min_d; cols <= max_d; ++cols) {
				write_mat_struct_def(f, rows, cols);
			}
		}
	}

	for (size_t d = min_d; d <= max_d; ++d) {
		write_vec_add_func(f, d);
		write_vec_scale_func(f, d);
		write_vec_dot_func(f, d);
	}

	if (write_mat) {
		for (size_t rows = min_d; rows <= max_d; ++rows) {
			for (size_t cols = min_d; cols <= max_d; ++cols) {
				write_mat_vec_mult_func(f, rows, cols);
			}
		}
	}
}

int main(void)
{
	FILE *f = fopen("linear_algebra.h", "wb");
	write_header(f);

	write_vec_structs(f, 2, 10, true);

	fclose(f);
	return 0;
}
