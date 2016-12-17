/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 23:18:06 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/17 00:07:35 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_radiosity(ENGINE *engine, CAST_RETURN *ret)
{
	VEC3		color;
	VEC3		radcolor;
	CAST_RETURN	radret;
	RAY			ray;

	color = new_vec3(0, 0, 0);

	ray = new_ray(vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.005f)), ret->intersect.normal);
	radret = cast_ray(engine, engine->active_scene, ray);
	if (radret.intersect.intersects)
	{
		radret.mtl.base_color = new_vec3((1 - radret.mtl.roughness) * (1 - ret->mtl.roughness), (1 - radret.mtl.roughness) * (1 - ret->mtl.roughness), (1 - radret.mtl.roughness) * (1 - ret->mtl.roughness));
		//float att = 1 / pow(vec3_distance(radret.intersect.position, ret->intersect.position), 2) * 1000.f;
		//printf("%f\n", att);
		radcolor = compute_lighting(engine, &radret);
		LIGHT light;
		light.type = POINT;
		light.attenuation = 0.002;
		light.color = radcolor;
		light.position = radret.intersect.position;
		light.power = (1 - radret.mtl.roughness) * (1 - ret->mtl.roughness);
		light.falloff = 100;
		color = compute_point_color(light, ret->mtl, ret->intersect, ray);
		color = vec3_mult(color, ret->mtl.base_color);
		/*if (radcolor.x && radcolor.y && radcolor.z)
			color = vec3_scale(radcolor, (1 - radret.mtl.roughness) * (1 - ret->mtl.roughness));*/
	}
	return (color);
}
