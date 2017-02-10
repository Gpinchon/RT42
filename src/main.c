/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 10:31:18 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"

static void			add_post_treatments(ENGINE *engine)
{
	t_callback		callback;

	callback = new_callback(ssao, engine);
	ezarray_push(&engine->post_treatments, &callback);
	callback = new_callback(depth_of_field, engine);
	ezarray_push(&engine->post_treatments, &callback);
	callback = new_callback(bloom, engine);
	ezarray_push(&engine->post_treatments, &callback);
	callback = new_callback(gamma_correction, engine);
	ezarray_push(&engine->post_treatments, &callback);
}

static inline void	init_rendering(ENGINE *e)
{
	UINT	i;

	clear_renderer(e);
	if (render_scene(e, &e->scene))
	{
		i = 0;
		while (i < e->post_treatments.length)
		{
			do_post_treatment(e, ezarray_get_index(e->post_treatments, i));
			if (++i < e->post_treatments.length)
				copy_framebuffer(e->finalbuffer, e->framebuffer);
		}
		display_framebuffer(e->finalbuffer, e->image);
		refresh_window(e->window);
		framework_loop(e->framework);
	}
}

int					main(int argc, char *argv[])
{
	ENGINE			e;
	t_value			val;

	if (argc < 2 || (argc == 2 && access(argv[1], 0 | F_OK | R_OK) != 0))
	{
		write(1, "Cannot find file !\n", 20);
		exit(0);
	}
	val = parser(argv[1]);
	e = create_scene(val);
	srandom(time(NULL));
	json_free(val);
	set_onexit_hook(e.framework, new_callback(destroy_engine, &e));
	add_post_treatments(&e);
	init_rendering(&e);
	return (0);
}
