/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_interp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:26:57 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/17 12:05:54 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec3_interp(float (*interp_function)(float, float, float),
	t_vec3 start, t_vec3 end, float percent)
{
	return ((t_vec3){
		interp_function(start.x, end.x, percent),
		interp_function(start.y, end.y, percent),
		interp_function(start.z, end.z, percent),
	});
}

t_vec4	vec4_interp(float (*interp_function)(float, float, float),
	t_vec4 start, t_vec4 end, float percent)
{
	return ((t_vec4){
		interp_function(start.x, end.x, percent),
		interp_function(start.y, end.y, percent),
		interp_function(start.z, end.z, percent),
		interp_function(start.w, end.w, percent),
	});
}
