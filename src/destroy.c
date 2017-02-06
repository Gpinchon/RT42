/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:46 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/06 22:02:46 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	destroy_materials(LINK *materials)
{
	LINK	*mtl[2];

	mtl[0] = materials;
	while (mtl[0])
	{
		mtl[1] = mtl[0]->next;
		free(((MATERIAL *)ezlink_get_data(mtl[0]))->name);
		mtl[0] = mtl[1];
	}
	destroy_ezchain(materials);
}

void	destroy_scene(SCENE *scene)
{
	destroy_ezarray(&scene->primitives);
	destroy_ezarray(&scene->lights);
	destroy_ezchain(scene->cameras);
	destroy_ezchain(scene->transforms);
	destroy_materials(scene->materials);
}

void	destroy_engine(ENGINE *engine)
{
	destroy_ezarray(&engine->framebuffer.array);
	destroy_ezarray(&engine->finalbuffer.array);
	destroy_ezarray(&engine->positionbuffer.array);
	destroy_ezarray(&engine->normalbuffer.array);
	destroy_ezarray(&engine->depthbuffer.array);
	destroy_ezarray(&engine->post_treatments);
	destroy_scene(&engine->scene);
	destroy_framework(engine->framework);
}
