/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/02 16:09:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework.h>
# include <vml.h>
# include <ezmem.h>
# include <stdio.h>

# define ENGINE			struct s_engine
# define SCENE			struct s_scene
# define FRAMEBUFFER	struct s_framebuffer
# define LIGHT			struct s_light
# define RTPRIMITIVE	struct s_rtprim
# define MATERIAL		struct s_mtl
# define CAMERA			struct s_camera
# define TRANSFORM		struct s_transform
# define CAST_RETURN	struct s_cast_return
# define UPVEC			(VEC3){0, 1, 0}
# define MAX_REFL		4
# define MAX_REFR		4
# define SAMPLING		1
# define WINDOW_SIZE	(t_point2){1024, 768}
# define BUFFER_SIZE	(t_point2){WINDOW_SIZE.x * SAMPLING, WINDOW_SIZE.y * SAMPLING}
# define CCLEAR_VALUE	0
# define FCLEAR_VALUE	0
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2
# define DIFFUSE		oren_nayar_diffuse
# define SPECULAR		trowbridge_reitz_specular
# define RENDER_NORMALS	false

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
	TRANSFORM	*target;
	UCHAR		type;
	UCHAR		cast_shadow;
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
	char		*name;
	void		*base_map;
	void		*normal_map;
	void		*metal_map;
	void		*rough_map;
	void		*ao_map;
	void		*height_map;
	VEC2		uv_scale;
	VEC3		base_color;
	VEC3		refraction_color;
	VEC3		reflection_color;
	LIGHT		emitting;
	float		roughness;
	float		metalness;
	float		refraction;
	float		alpha;
	float		parallax;
}				t_mtl;

typedef struct	s_rtprim
{
	UCHAR		transformed;
	TRANSFORM	*transform;
	MATERIAL	*material;
	PRIMITIVE	prim;
}				t_rtprim;

typedef struct	s_camera
{
	TRANSFORM	*transform;
	float		fov;
	float		znear;
	float		zfar;
	RAY			ray;
	MAT4		m4_view;
}				t_camera;

typedef struct	s_scene
{
	CAMERA		*active_camera;
	ARRAY		primitives;
	ARRAY		lights;
	LINK		*cameras;
	LINK		*transforms;
	LINK		*materials;
}				t_scene;

typedef struct	s_framebuffer
{
	Uint8		bpp;
	Uint8		opp;
	UINT		sizeline;
	t_point2	size;
	ARRAY		array;
}				t_framebuffer;

typedef struct	s_cast_return
{
	INTERSECT	intersect;
	MATERIAL	mtl;
	MAT3		tbn;
}				t_cast_return;

typedef struct	s_engine
{
	BOOL		stop_rendering;
	UINT		max_refr;
	UINT		max_refl;
	UINT		refl_iteration;
	UINT		refr_iteration;
	void		*framework;
	void		*window;
	void		*image;
	void		*loading_screen;
	INTERSECT	(*inter_functions[10])(PRIMITIVE, RAY);
	VEC2		(*uv_functions[10])(PRIMITIVE, INTERSECT);
	void		(*progress_callback)(ENGINE*, float);
	Uint32		last_time;
	SCENE		*active_scene;
	FRAMEBUFFER	framebuffer;
	FRAMEBUFFER	positionbuffer;
	FRAMEBUFFER	normalbuffer;
	FRAMEBUFFER	mtlbuffer;
	FRAMEBUFFER	depthbuffer;
	SCENE		scene;
	VEC2		poisson_disc[64];
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
void			generate_poisson_disc(VEC2 *disc, UINT disc_size, float min_dist, VEC2 limits);
float			frand_a_b(float a, float b);

t_point2		map_uv(void *image, VEC2 uv);
float			color_to_factor(VEC3 color);
VEC2			sphere_uv(PRIMITIVE sphere, INTERSECT inter);
VEC2			cylinder_uv(PRIMITIVE cylinder, INTERSECT inter);
VEC2			plane_uv(PRIMITIVE plane, INTERSECT inter);
VEC3			sample_texture(void *image, VEC2 uv);
VEC3			sample_texture_filtered(void *image, VEC2 uv);

CAST_RETURN		cast_ray(ENGINE *engine, SCENE *scene, RAY ray);
VEC3			compute_lighting(ENGINE *engine, CAST_RETURN *ret);
VEC3			compute_refraction(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray, float aior);
VEC3			compute_reflection(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray);
VEC3			compute_radiosity(ENGINE *engine, CAST_RETURN *ret);
void			update_transform(TRANSFORM *transform);

void			destroy_scene(SCENE *scene);
void			destroy_engine(ENGINE *engine);

TRANSFORM		*new_transform(SCENE *scene, VEC3 position, VEC3 rotation, VEC3 scale);
RTPRIMITIVE		*new_rtprim(SCENE *scene);
MATERIAL		*new_material(SCENE *scene, char *name);
CAMERA			*new_camera(SCENE *scene, float fov, float znear, float zfar);
LIGHT			*new_light(SCENE *scene, UCHAR type, VEC3 position);

MATERIAL		*get_mtl_by_name(SCENE *scene, char *name);
MATERIAL		*mtl_aquamarine(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_greasy_metal(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_rusted_metal(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_rock_copper(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_rock_sliced(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_granite(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_water(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_brick(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_harshbricks(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_octostone(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_scuffed_plastic_red(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_scuffed_aluminium(ENGINE *engine, SCENE *scene);

void			clear_renderer(ENGINE *engine);
void			clear_buffers(ENGINE *engine);
void			clear_uchar_bits(void *pixel);
void			clear_float_bits(void *pixel);

float			trowbridge_reitz_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, MATERIAL mtl);
float			blinn_phong_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl mtl);
float			oren_nayar_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl mtl);
float			lambert_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl mtl);
VEC3			compute_lightdir(t_light l, VEC3 position);
VEC3			compute_point_color(LIGHT l, MATERIAL mtl,
				INTERSECT inter, RAY ray);

#endif