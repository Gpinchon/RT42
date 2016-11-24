/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/25 00:10:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework.h>
# include <vml.h>
# include <ezmem.h>
#include <stdio.h>
# define ENGINE			struct s_engine
# define SCENE			struct s_scene
# define FRAMEBUFFER	struct s_framebuffer
# define LIGHT			struct s_light
# define RTPRIMITIVE	struct s_rtprim
# define MATERIAL		struct s_mtl
# define CAMERA			struct s_camera
# define TRANSFORM		struct s_transform
# define UPVEC			(VEC3){0, 1, 0}
# define SUPERSAMPLING	1
# define WINDOW_SIZE	(t_point2){1024, 768}
# define WS				WINDOW_SIZE
# define BUFFER_SIZE	(t_point2){WS.x * SUPERSAMPLING, WS.y * SUPERSAMPLING}
# define CCLEAR_VALUE	125
# define FCLEAR_VALUE	0
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2
# define DIFFUSE		oren_nayar_diffuse
# define SPECULAR		trowbridge_reitz_specular

typedef struct	s_transform
{
	UCHAR		updated;
	TRANSFORM	*parent;
	TRANSFORM	*target;
	VEC3		position;
	VEC3		rotation;
	VEC3		scaling;
	VEC3		up;
	MAT4		matrix;
	MAT4		translate;
	MAT4		rotate;
	MAT4		scale;
}				t_transform;

typedef struct	s_light
{
	UCHAR		type;
	float		power;
	float		attenuation;
	float		falloff;
	float		spot_size;
	VEC3		color;
	VEC3		position;
	VEC3		direction;
}				t_light;

typedef struct	s_mtl
{
	VEC3		base_color;
	float		roughness;
	float		metalness;
	float		alpha;
}				t_mtl;

typedef struct	s_rtprim
{
	TRANSFORM	*transform;
	MATERIAL	*material;
	PRIMITIVE	prim;
}				t_rtprim;

typedef struct	s_camera
{
	TRANSFORM	*transform;
	RAY			ray;
	MAT4		m4_view;
	float		fov;
}				t_camera;

typedef struct	s_scene
{
	CAMERA		*active_camera;
	ARRAY		primitive;
	ARRAY		light;
	ARRAY		camera;
	LINK		*transform;
	LINK		*material;
}				t_scene;

typedef struct	s_framebuffer
{
	Uint8		bpp;
	Uint8		opp;
	UINT		sizeline;
	t_point2	size;
	ARRAY		array;
}				t_framebuffer;

typedef struct	s_engine
{
	void		*framework;
	void		*window;
	void		*image;
	FRAMEBUFFER	framebuffer;
	FRAMEBUFFER	depthbuffer;
	FRAMEBUFFER	normalbuffer;
	FRAMEBUFFER	mtlbuffer;
	SCENE		scene;
	INTERSECT	(*inter_functions[10])(PRIMITIVE, RAY);
}				t_engine;

FRAMEBUFFER		new_framebuffer(TYPE type, t_point2 size, Uint8 depth);
SCENE			new_scene();
ENGINE			new_engine();
void			put_pixel_to_buffer(FRAMEBUFFER buffer,
				t_point2 coord, VEC4 color);
void			put_value_to_buffer(FRAMEBUFFER buffer,
				t_point2 coord, float value);
void			*get_buffer_value(FRAMEBUFFER buffer,
				t_point2 coord);


void			destroy_scene(SCENE *scene);
void			destroy_engine(ENGINE *engine);

TRANSFORM		*new_transform(SCENE *scene, VEC3 position, VEC3 rotation, VEC3 scale);
RTPRIMITIVE		*new_rtprim(SCENE *scene);
MATERIAL		*new_material(SCENE *scene);
CAMERA			*new_camera(SCENE *scene, float fov);

void			clear_renderer(ENGINE *engine);
void			clear_buffers(ENGINE *engine);
void			clear_uchar_bits(void *pixel);
void			clear_float_bits(void *pixel);

float			trowbridge_reitz_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, float s);
float			blinn_phong_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, float s);
float			oren_nayar_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl mtl);
float			lambert_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl mtl);
VEC3			compute_lightdir(t_light l, VEC3 position);

#endif