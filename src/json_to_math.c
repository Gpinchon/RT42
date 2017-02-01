/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:16:20 by mbarbari          #+#    #+#             */
/*   Updated: 2017/01/31 18:23:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

VEC3		get_vec3_json(t_value val)
{
	if (val.error == TYPE_ERROR)
		return (new_vec3(0.0, 0.0, 0.0));
	return (new_vec3(	json_get(val.data.obj, "x").data.number,
						json_get(val.data.obj, "y").data.number,
						json_get(val.data.obj, "z").data.number));
}

VEC2		get_vec2_json(t_value val)
{
	if (val.error == TYPE_ERROR)
		return (new_vec2(0.0, 0.0));
	return (new_vec2(	json_get(val.data.obj, "x").data.number,
						json_get(val.data.obj, "y").data.number));
}
