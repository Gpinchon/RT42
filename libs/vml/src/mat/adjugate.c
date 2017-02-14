/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjugate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:00:03 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/20 17:40:09 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

/*
** returns the transposed cofactor matrix
*/

inline t_mat2	mat2_adjugate(const t_mat2 m)
{
	return (mat2_transpose(mat2_cofactor(m)));
}

inline t_mat3	mat3_adjugate(const t_mat3 m)
{
	return (mat3_transpose(mat3_cofactor(m)));
}

inline t_mat4	mat4_adjugate(const t_mat4 m)
{
	return (mat4_transpose(mat4_cofactor(m)));
}
