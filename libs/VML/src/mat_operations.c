/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:38:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 16:36:18 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	m4_inverse1(t_mat4 *t, const t_mat4 i)
{
	t->m[0] = i.m[5]  * i.m[10] * i.m[15] - i.m[5]  * i.m[11] * i.m[14] -
		i.m[9]  * i.m[6]  * i.m[15] + i.m[9]  * i.m[7]  * i.m[14] +
		i.m[13] * i.m[6]  * i.m[11] - i.m[13] * i.m[7]  * i.m[10];
	t->m[4] = -i.m[4]  * i.m[10] * i.m[15] + i.m[4]  * i.m[11] * i.m[14] +
		i.m[8]  * i.m[6]  * i.m[15] - i.m[8]  * i.m[7]  * i.m[14] -
		i.m[12] * i.m[6]  * i.m[11] + i.m[12] * i.m[7]  * i.m[10];
	t->m[8] = i.m[4]  * i.m[9] * i.m[15] - i.m[4]  * i.m[11] * i.m[13] -
		i.m[8]  * i.m[5] * i.m[15] + i.m[8]  * i.m[7] * i.m[13] +
		i.m[12] * i.m[5] * i.m[11] - i.m[12] * i.m[7] * i.m[9];
	t->m[12] = -i.m[4]  * i.m[9] * i.m[14] + i.m[4]  * i.m[10] * i.m[13] +
		i.m[8]  * i.m[5] * i.m[14] - i.m[8]  * i.m[6] * i.m[13] -
		i.m[12] * i.m[5] * i.m[10] + i.m[12] * i.m[6] * i.m[9];
	t->m[1] = -i.m[1]  * i.m[10] * i.m[15] + i.m[1]  * i.m[11] * i.m[14] +
		i.m[9]  * i.m[2] * i.m[15] - i.m[9]  * i.m[3] * i.m[14] -
		i.m[13] * i.m[2] * i.m[11] + i.m[13] * i.m[3] * i.m[10];
	t->m[5] = i.m[0]  * i.m[10] * i.m[15] - i.m[0]  * i.m[11] * i.m[14] -
		i.m[8]  * i.m[2] * i.m[15] + i.m[8]  * i.m[3] * i.m[14] +
		i.m[12] * i.m[2] * i.m[11] - i.m[12] * i.m[3] * i.m[10];
	t->m[9] = -i.m[0]  * i.m[9] * i.m[15] + i.m[0]  * i.m[11] * i.m[13] +
		i.m[8]  * i.m[1] * i.m[15] - i.m[8]  * i.m[3] * i.m[13] -
		i.m[12] * i.m[1] * i.m[11] + i.m[12] * i.m[3] * i.m[9];
	t->m[13] = i.m[0]  * i.m[9] * i.m[14] - i.m[0]  * i.m[10] * i.m[13] -
		i.m[8]  * i.m[1] * i.m[14] + i.m[8]  * i.m[2] * i.m[13] +
		i.m[12] * i.m[1] * i.m[10] - i.m[12] * i.m[2] * i.m[9];
}

static void	m4_inverse2(t_mat4 *t, const t_mat4 i)
{
	t->m[2] = i.m[1]  * i.m[6] * i.m[15] - i.m[1]  * i.m[7] * i.m[14] -
		i.m[5]  * i.m[2] * i.m[15] + i.m[5]  * i.m[3] * i.m[14] +
		i.m[13] * i.m[2] * i.m[7] - i.m[13] * i.m[3] * i.m[6];
	t->m[6] = -i.m[0]  * i.m[6] * i.m[15] + i.m[0]  * i.m[7] * i.m[14] +
		i.m[4]  * i.m[2] * i.m[15] - i.m[4]  * i.m[3] * i.m[14] -
		i.m[12] * i.m[2] * i.m[7] + i.m[12] * i.m[3] * i.m[6];
	t->m[10] = i.m[0]  * i.m[5] * i.m[15] - i.m[0]  * i.m[7] * i.m[13] -
		i.m[4]  * i.m[1] * i.m[15] + i.m[4]  * i.m[3] * i.m[13] +
		i.m[12] * i.m[1] * i.m[7] - i.m[12] * i.m[3] * i.m[5];
	t->m[14] = -i.m[0]  * i.m[5] * i.m[14] + i.m[0]  * i.m[6] * i.m[13] +
		i.m[4]  * i.m[1] * i.m[14] - i.m[4]  * i.m[2] * i.m[13] -
		i.m[12] * i.m[1] * i.m[6] + i.m[12] * i.m[2] * i.m[5];
	t->m[3] = -i.m[1] * i.m[6] * i.m[11] + i.m[1] * i.m[7] * i.m[10] +
		i.m[5] * i.m[2] * i.m[11] - i.m[5] * i.m[3] * i.m[10] -
		i.m[9] * i.m[2] * i.m[7] + i.m[9] * i.m[3] * i.m[6];
	t->m[7] = i.m[0] * i.m[6] * i.m[11] - i.m[0] * i.m[7] * i.m[10] -
		i.m[4] * i.m[2] * i.m[11] + i.m[4] * i.m[3] * i.m[10] +
		i.m[8] * i.m[2] * i.m[7] - i.m[8] * i.m[3] * i.m[6];
	t->m[11] = -i.m[0] * i.m[5] * i.m[11] + i.m[0] * i.m[7] * i.m[9] +
		i.m[4] * i.m[1] * i.m[11] - i.m[4] * i.m[3] * i.m[9] -
		i.m[8] * i.m[1] * i.m[7] + i.m[8] * i.m[3] * i.m[5];
	t->m[15] = i.m[0] * i.m[5] * i.m[10] - i.m[0] * i.m[6] * i.m[9] -
		i.m[4] * i.m[1] * i.m[10] + i.m[4] * i.m[2] * i.m[9] +
		i.m[8] * i.m[1] * i.m[6] - i.m[8] * i.m[2] * i.m[5];
}

t_mat4	mat4_inverse(const t_mat4 i)
{
	t_mat4 t;
	GLfloat det;
	int j;

	m4_inverse1(&t, i);
	m4_inverse2(&t, i);
	det = i.m[0] * t.m[0] + i.m[1] * t.m[4] + i.m[2] * t.m[8] + i.m[3] * t.m[12];
	if (det == 0)
		return m4_zero();
	det = 1.0 / det;
	j = 0;
	while (j < 16)
	{
		t.m[j] = t.m[j] * det;
		j++;
	}
	return (t);
}

t_mat4	mat4_transpose(const t_mat4 in)
{
	int		x;
	int		z;
	t_mat4	out;

	z = 0;
	while (z < 4)
	{
		x = 0;
		while (x < 4)
		{
			out.m[(z * 4) + x] = in.m[(x * 4) + z];
			x++;
		}
		z++;
	}
	return (out);
}