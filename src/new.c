/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/11 00:48:02 by gpinchon         ###   ########.fr       */
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

SCENE		new_scene()
{
	SCENE	scene;

	memset(&scene, 0, sizeof(SCENE));
	return (scene);
}

ENGINE		new_engine(t_engine_opt options)
{
	ENGINE	engine;

	memset(&engine, 0, sizeof(ENGINE));
	engine.framework = new_framework();
	engine.window = new_window(engine.framework, options.window_size.x, options.window_size.y, "RT");
	set_loop_hook(engine.framework, new_callback((void(*)(void*))refresh_window, engine.window));
	engine.progress_callback = print_progress;
	engine.loading_screen = load_image_file(engine.framework, "./res/loading_screen.bmp");
	engine.image = new_image(engine.framework, options.window_size.x, options.window_size.y);
	engine.framebuffer = new_framebuffer(unsigned_char, options.internal_size, 4);
	engine.finalbuffer = new_framebuffer(unsigned_char, options.internal_size, 4);
	//engine.brightbuffer = new_framebuffer(FLOAT, options.internal_size, 3);
	engine.positionbuffer = new_framebuffer(FLOAT, options.internal_size, 3);
	engine.normalbuffer = new_framebuffer(FLOAT, options.internal_size, 3);
	engine.depthbuffer = new_framebuffer(FLOAT, options.internal_size, 1);
	engine.mtlbuffer = new_framebuffer(FLOAT, options.internal_size, sizeof(t_mtl) / sizeof(float));
	engine.post_treatments = new_ezarray(other, 0, sizeof(t_callback));
	attach_image_to_window(engine.window, engine.image);
	engine.inter_functions[cone] = intersect_cone;
	engine.inter_functions[sphere] = intersect_sphere;
	engine.inter_functions[cylinder] = intersect_cylinder;
	engine.inter_functions[plane] = intersect_plane;
	engine.inter_functions[triangle] = intersect_triangle;
	engine.inter_functions[disc] = intersect_disc;
	engine.uv_functions[cone] = cylinder_uv;
	engine.uv_functions[sphere] = sphere_uv;
	engine.uv_functions[cylinder] = cylinder_uv;
	engine.uv_functions[capped_cylinder] = cylinder_uv;
	engine.uv_functions[plane] = plane_uv;
	engine.uv_functions[disc] = plane_uv;
	engine.max_refl = options.max_refl;
	engine.max_refr = options.max_refr;
	engine.area_sampling = options.area_sampling;
	generate_poisson_disc(engine.poisson_disc, 64, 0.05f, new_vec2(0, 1));
	return (engine);
}
