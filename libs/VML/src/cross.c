/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:04:06 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/12 19:25:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../VML.h"

t_vec3	vec3_cross_vec3(t_vec3 vector1, t_vec3 vector2)
{
	return ((t_vec3){
		vector1.y * vector2.z - vector1.z * vector2.y,
		vector1.z * vector2.x - vector1.x * vector2.z,
		vector1.x * vector2.y - vector1.y * vector2.x
	});
}
