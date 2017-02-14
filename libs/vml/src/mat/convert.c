/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:17:46 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:53:20 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

MAT2			mat3_to_mat2(MAT3 m)
{
	return ((MAT2){.m = {
		m.m[0], m.m[1],
		m.m[3], m.m[4]
	}});
}

MAT3			mat2_to_mat3(MAT2 m)
{
	return ((MAT3){.m = {
		m.m[0], m.m[1], 0,
		m.m[2], m.m[3], 0,
		0, 0, 1
	}});
}

t_mat3			mat4_to_mat3(t_mat4 m)
{
	return ((t_mat3){.m = {
		m.m[0], m.m[1], m.m[2],
		m.m[4], m.m[5], m.m[6],
		m.m[8], m.m[9], m.m[10]
	}});
}

t_mat4			mat3_to_mat4(t_mat3 m)
{
	return ((t_mat4){.m = {
		m.m[0], m.m[1], m.m[2], 0,
		m.m[3], m.m[4], m.m[5], 0,
		m.m[6], m.m[7], m.m[8], 0,
		0, 0, 0, 1
	}});
}
