/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:20:11 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/20 17:40:45 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

inline t_mat2	mat2_cofactor(const t_mat2 m)
{
	t_mat2	minors;

	minors = mat2_minors(m);
	return ((t_mat2){.m = {
		minors.m[0], -minors.m[1],
		-minors.m[2], minors.m[3]
	}});
}

inline t_mat3	mat3_cofactor(const t_mat3 m)
{
	t_mat3	minors;

	minors = mat3_minors(m);
	return ((t_mat3){.m = {
		minors.m[0], -minors.m[1], minors.m[2],
		-minors.m[3], minors.m[4], -minors.m[5],
		minors.m[6], -minors.m[7], minors.m[8]
	}});
}

inline t_mat4	mat4_cofactor(const t_mat4 m)
{
	t_mat4	minors;

	minors = mat4_minors(m);
	return ((t_mat4){.m = {
		minors.m[0], -minors.m[1], minors.m[2], -minors.m[3],
		-minors.m[4], minors.m[5], -minors.m[6], minors.m[7],
		minors.m[8], -minors.m[9], minors.m[10], -minors.m[11],
		-minors.m[12], minors.m[13], -minors.m[14], minors.m[15]
	}});
}
