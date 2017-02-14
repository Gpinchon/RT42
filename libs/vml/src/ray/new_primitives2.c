/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_primitives2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:41:06 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:04:53 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

PRIMITIVE	new_disc(float radius)
{
	PRIMITIVE	p;

	p = new_primitive(disc);
	p.data.disc.radius = radius;
	p.data.disc.radius2 = radius * radius;
	return (p);
}

PRIMITIVE	new_plane(void)
{
	PRIMITIVE	p;

	p = new_primitive(plane);
	return (p);
}
