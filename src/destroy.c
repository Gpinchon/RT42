/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 11:30:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	destroy_scene(SCENE *scene)
{
	destroy_ezarray(&scene->primitive);
	destroy_ezarray(&scene->light);
	destroy_ezarray(&scene->material);
	destroy_ezarray(&scene->camera);
	destroy_ezarray(&scene->transform);
}

void		destroy_engine(ENGINE *engine)
{
	destroy_ezarray(&engine->framebuffer.array);
	destroy_ezarray(&engine->depthbuffer.array);
	destroy_ezarray(&engine->normalbuffer.array);
	destroy_ezarray(&engine->mtlbuffer.array);
}
