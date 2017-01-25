/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:46 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/25 18:34:30 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	destroy_scene(SCENE *scene)
{
	destroy_ezarray(&scene->primitives);
	destroy_ezarray(&scene->lights);
	destroy_ezchain(scene->cameras);
	destroy_ezchain(scene->transforms);
	destroy_ezchain(scene->materials);
}

void		destroy_engine(ENGINE *engine)
{
	destroy_ezarray(&engine->framebuffer.array);
	destroy_ezarray(&engine->positionbuffer.array);
	destroy_ezarray(&engine->normalbuffer.array);
	//destroy_ezarray(&engine->mtlbuffer.array);
	destroy_scene(&engine->scene);
}
