/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:19:24 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/10 17:03:36 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <vml.h>

void	mat2_print(MAT2 m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%c%f\t", !(i % 2) ? '\n' : 0, m.m[i]);
		i++;
	}
	printf("\n\n");
}

void	mat3_print(MAT3 m)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		printf("%c%f\t", !(i % 3) ? '\n' : 0, m.m[i]);
		i++;
	}
	printf("\n\n");
}

void	mat4_print(MAT4 m)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		printf("%c%f\t", !(i % 4) ? '\n' : 0, m.m[i]);
		i++;
	}
	printf("\n\n");
}

void	mat2_assert(MAT2 m, MAT2 m1)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!float_equal(m.m[i], m1.m[i]))
		{
			printf("Assertion failed at index : %i\n\
Value : %f, Expected : %f\n", i, m.m[i], m1.m[i]);
			exit(-42);
		}
		i++;
	}
	printf("Verification passed !\n\n");
}

void	mat3_assert(MAT3 m, MAT3 m1)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (!float_equal(m.m[i], m1.m[i]))
		{
			printf("Assertion failed at index : %i\n\
Value : %f, Expected : %f\n", i, m.m[i], m1.m[i]);
			exit(-42);
		}
		i++;
	}
	printf("Verification passed !\n\n");
}

void	mat4_assert(MAT4 m, MAT4 m1)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!float_equal(m.m[i], m1.m[i]))
		{
			printf("Assertion failed at index : %i\n\
Value : %f, Expected : %f\n", i, m.m[i], m1.m[i]);
			exit(-42);
		}
		i++;
	}
	printf("Verification passed !\n\n");
}

void	test_mat2()
{
	MAT2	matrix;
	MAT2	temp;

	printf("Da matrix :\n");
	mat2_print(matrix = (MAT2){.m = {
			1, -2,
			6, 3
		}});
	printf("Determinant :\n");
	printf("\n%f\n\n", mat2_determinant(matrix));
	printf("Minors :\n");
	mat2_print(temp = mat2_minors(matrix));
	mat2_assert(temp, (MAT2){.m = {
		3, 6,
		-2, 1
	}});
	printf("Cofactors :\n");
	mat2_print(temp = mat2_cofactor(matrix));
	mat2_assert(temp, (MAT2){.m = {
		3, -6,
		2, 1
	}});
	printf("Adjugate :\n");
	mat2_print(temp = mat2_adjugate(matrix));
	mat2_assert(temp, (MAT2){.m = {
		3, 2,
		-6, 1
	}});
	printf("Inverse :\n");
	mat2_print(temp = mat2_inverse(matrix));
	mat2_assert(temp, (MAT2){.m = {
		3/15.f, 2/15.f,
		-6/15.f, 1/15.f,
	}});
}

void	test_mat3()
{
	MAT3	matrix;
	MAT3	temp;

	printf("Da matrix :\n");
	mat3_print(matrix = (MAT3){.m = {
			1, -1, 0,
			6, 1, 3,
			7, 15, -2
		}});
	printf("Determinant :\n");
	printf("\n%f\n\n", mat3_determinant(matrix));
	printf("Minors :\n");
	mat3_print(temp = mat3_minors(matrix));
	mat3_assert(temp, (MAT3){.m = {
		-47, -33, 83,
		2, -2, 22,
		-3, 3, 7
	}});
	printf("Cofactors :\n");
	mat3_print(temp = mat3_cofactor(matrix));
	mat3_assert(temp, (MAT3){.m = {
		-47, 33, 83,
		-2, -2, -22,
		-3, -3, 7
	}});
	printf("Adjugate :\n");
	mat3_print(temp = mat3_adjugate(matrix));
	mat3_assert(temp, (MAT3){.m = {
		-47, -2, -3,
		33, -2, -3,
		83, -22, 7
	}});
	printf("Inverse :\n");
	mat3_print(temp = mat3_inverse(matrix));
	mat3_assert(temp, (MAT3){.m = {
		47/80.f, 2/80.f, 3/80.f,
		-33/80.f, 2/80.f, 3/80.f,
		-83/80.f, 22/80.f, -7/80.f
	}});
}

void	test_mat4()
{
	MAT4	matrix;
	MAT4	temp;

	printf("Da matrix :\n");
	mat4_print(matrix = (MAT4){.m = {
			1, -1, 0, 4,
			6, 1, 3, 10,
			7, 15, -2, 5,
			20, 9, 8, 1
		}});
	printf("Determinant :\n");
	printf("\n%f\n\n", mat4_determinant(matrix));
	printf("Minors :\n");
	mat4_print(temp = mat4_minors(matrix));
	mat4_assert(temp, (MAT4){.m = {
		1428, 987, -2457, 21,
		594, 342, -1071, 234,
		1, -125, -147, -31,
		-223, -97, 147, -80
	}});
	printf("Cofactors :\n");
	mat4_print(temp = mat4_cofactor(matrix));
	mat4_assert(temp, (MAT4){.m = {
		1428, -987, -2457, -21,
		-594, 342, 1071, 234,
		1, 125, -147, 31,
		223, -97, -147, -80
	}});
	printf("Adjugate :\n");
	mat4_print(temp = mat4_adjugate(matrix));
	mat4_assert(temp, (MAT4){.m = {
		1428, -594, 1, 223,
		-987, 342, 125, -97,
		-2457, 1071, -147, -147,
		-21, 234, 31, -80
	}});
	printf("Inverse :\n");
	mat4_print(temp = mat4_inverse(matrix));
	mat4_assert(temp, (MAT4){.m = {
		1428 / 2331.f, -594 / 2331.f, 1 / 2331.f, 223 / 2331.f,
		-987 / 2331.f, 342 / 2331.f, 125 / 2331.f, -97 / 2331.f,
		-2457 / 2331.f, 1071 / 2331.f, -147 / 2331.f, -147 / 2331.f,
		-21 / 2331.f, 234 / 2331.f, 31 / 2331.f, -80 / 2331.f
	}});
}

int main(void)
{
	printf("\n\nCHECKING MAT2\n");
	test_mat2();
	printf("\n\nCHECKING MAT3\n");
	test_mat3();
	printf("\n\nCHECKING MAT4\n");
	test_mat4();
	return (0);
}