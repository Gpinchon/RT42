/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:38:09 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:53:57 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat2		mat2_inverse(const t_mat2 m)
{
	return (mat2_fmult(mat2_adjugate(m), 1.0 / mat2_determinant(m)));
}

/*
** m[0] m[1] m[2]
** m[3] m[4] m[5]
** m[6] m[7] m[8]
**
** m[4] m[5]	m[3] m[5]	m[3] m[4]
** m[7] m[8]	m[6] m[8]	m[6] m[7]
**
** m[1] m[2]	m[0] m[2]	m[0] m[1]
** m[7] m[8]	m[6] m[8]	m[6] m[7]
**
** m[1] m[2]	m[0] m[2]	m[0] m[1]
** m[4] m[5]	m[3] m[5]	m[3] m[4]
*/

t_mat3		mat3_inverse(const t_mat3 m)
{
	return (mat3_fmult(mat3_adjugate(m), 1.0 / mat3_determinant(m)));
}

t_mat4		mat4_inverse(const t_mat4 m)
{
	return (mat4_fmult(mat4_adjugate(m), 1.0 / mat4_determinant(m)));
}
