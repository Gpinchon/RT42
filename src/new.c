/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/08 18:30:05 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

FRAMEBUFFER	new_framebuffer(TYPE type, t_point2 size, Uint8 depth)
{
	FRAMEBUFFER	buffer;

	buffer.array = new_ezarray(type, size.x * size.y * depth);
	buffer.size = size;
	buffer.opp = depth;
	buffer.bpp = buffer.opp * 8;
	buffer.sizeline = size.x * buffer.opp;
	return (buffer);
}

SCENE		new_scene(void)
{
	SCENE	scene;

	memset(&scene, 0, sizeof(SCENE));
	return (scene);
}

void		create_framebuffers(ENGINE *engine, t_engine_opt opt)
{
	engine->framebuffer = new_framebuffer(unsigned_char, opt.internal_size, 4);
	engine->finalbuffer = new_framebuffer(unsigned_char, opt.internal_size, 4);
	engine->positionbuffer = new_framebuffer(FLOAT, opt.internal_size, 3);
	engine->normalbuffer = new_framebuffer(FLOAT, opt.internal_size, 3);
	engine->depthbuffer = new_framebuffer(FLOAT, opt.internal_size, 1);
}

void		assign_functions(ENGINE *engine)
{
	engine->inter_functions[cone] = intersect_cone;
	engine->inter_functions[sphere] = intersect_sphere;
	engine->inter_functions[cylinder] = intersect_cylinder;
	engine->inter_functions[plane] = intersect_plane;
	engine->inter_functions[triangle] = intersect_triangle;
	engine->inter_functions[disc] = intersect_disc;
	engine->uv_functions[cone] = cylinder_uv;
	engine->uv_functions[sphere] = sphere_uv;
	engine->uv_functions[cylinder] = cylinder_uv;
	engine->uv_functions[plane] = plane_uv;
	engine->uv_functions[triangle] = plane_uv;
	engine->uv_functions[disc] = plane_uv;
}

ENGINE		new_engine(t_engine_opt o)
{
	ENGINE	e;

	memset(&e, 0, sizeof(ENGINE));
	e.framework = new_framework();
	e.window = new_window(e.framework, o.window_size.x, o.window_size.y, "RT");
	set_loop_hook(e.framework, new_callback((void(*)(void*))refresh_window,
		e.window));
	e.progress_callback = print_progress;
	e.loading_screen = load_image_file(e.framework, "./res/loading_screen.bmp");
	e.image = new_image(e.framework, o.window_size.x, o.window_size.y);
	attach_image_to_window(e.window, e.image);
	create_framebuffers(&e, o);
	e.post_treatments = new_ezarray(other, 0, sizeof(t_callback));
	assign_functions(&e);
	e.max_refl = o.max_refl;
	e.max_refr = o.max_refr;
	e.area_sampling = o.area_sampling;
	generate_poisson_disc(e.poisson_disc, 64, 0.05f, new_vec2(0, 1));
	return (e);
}
