/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:26:03 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/17 12:05:01 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec3_add_vec3(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x + v1.x,
		v.y + v1.y,
		v.z + v1.z
	});
}

t_vec4	vec4_add_vec4(t_vec4 v, t_vec4 v1)
{
	return ((t_vec4){
		v.x + v1.x,
		v.y + v1.y,
		v.z + v1.z,
		v.w + v1.w
	});
}
