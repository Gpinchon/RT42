/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 11:29:42 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework.h>
# include <vml.h>
# include <ezmem.h>
# define ENGINE			struct s_engine
# define SCENE			struct s_scene
# define FRAMEBUFFER	struct s_framebuffer
# define LIGHT			struct s_light
# define RTPRIMITIVE	struct s_rtprim
# define MATERIAL		struct s_mtl
# define CAMERA			struct s_camera
# define TRANSFORM		struct s_transform
# define SUPERSAMPLING	4
# define WINDOW_SIZE	(t_point2){512, 512}
# define WS				WINDOW_SIZE
# define BUFFER_SIZE	(t_point2){WS.x * SUPERSAMPLING, WS.y * SUPERSAMPLING}
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2

typedef struct	s_transform
{
	UCHAR		updated;
	TRANSFORM	*parent;
	VEC3		position;
	VEC3		rotation;
	VEC3		scale;
	MAT4		matrix;
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
	float		metallic;
	float		specular;
	float		alpha;
}				t_mtl;

typedef struct	s_rtprim
{
	TRANSFORM	*transform;
	MATERIAL	*material;
	PRIMITIVE	prim;
	PRIMITIVE	tranformed_prim;
}				t_rtprim;

typedef struct	s_camera
{
	TRANSFORM	*transform;
	RAY			ray;
	MAT4		m4_view;
}				t_camera;

typedef struct	s_scene
{
	UINT		active_camera;
	ARRAY		primitive;
	ARRAY		light;
	ARRAY		material;
	ARRAY		camera;
	ARRAY		transform;
}				t_scene;

typedef struct	s_framebuffer
{
	Uint8		bpp;
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
}				t_engine;

FRAMEBUFFER		new_framebuffer(TYPE type, t_point2 size, Uint8 depth);
SCENE			new_scene();
ENGINE			new_engine();

void			destroy_scene(SCENE *scene);
void			destroy_engine(ENGINE *engine);

TRANSFORM		*new_transform(SCENE scene, VEC3 position, VEC3 rotation, VEC3 scale);
RTPRIMITIVE		*new_rtprim(SCENE scene, PRIM_TYPE type);
MATERIAL		*new_material(SCENE scene);
CAMERA			*new_camera(SCENE scene);

#endif