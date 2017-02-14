/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:57:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:05:31 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

RAY			new_ray(VEC3 origin, VEC3 direction)
{
	return ((RAY){origin, direction});
}

INTERSECT	new_intersect(void)
{
	INTERSECT	intersect;

	vml_memset(&intersect, 0, sizeof(INTERSECT));
	return (intersect);
}

PRIMITIVE	new_primitive(PRIM_TYPE type)
{
	PRIMITIVE	primitive;

	vml_memset(&primitive, 0, sizeof(PRIMITIVE));
	primitive.type = type;
	return (primitive);
}
