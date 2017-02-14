/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 23:16:56 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:54:18 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	mat3_mult_vec2(t_mat3 m, t_vec2 v)
{
	return ((t_vec2){
		m.m[0] * v.x + m.m[1] * v.y + m.m[2],
		m.m[3] * v.x + m.m[4] * v.y + m.m[5]
	});
}

t_vec2	mat2_mult_vec2(t_mat2 m, t_vec2 v)
{
	return ((t_vec2){
		m.m[0] * v.x + m.m[2] * v.y,
		m.m[1] * v.x + m.m[3] * v.y
	});
}
