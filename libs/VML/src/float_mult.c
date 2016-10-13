/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:46:00 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 18:46:03 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3 vec3_mult_float(t_vec3 v, float f)
{
	return ((t_vec3){
		v.x * f,
		v.y * f,
		v.z * f
	});
}

t_vec4 vec4_mult_float(t_vec4 v, float f)
{
	return ((t_vec4){
		v.x * f,
		v.y * f,
		v.z * f,
		v.w * f
	});
}