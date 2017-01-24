/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/24 18:59:00 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework.h>
# include <vml.h>
# include <ezmem.h>
# include <time.h>

# define ENGINE			struct s_engine
# define SCENE			struct s_scene
# define FRAMEBUFFER	struct s_framebuffer
# define LIGHT			struct s_light
# define RTPRIMITIVE	struct s_rtprim
# define MATERIAL		struct s_mtl
# define CAMERA			struct s_camera
# define RTTRANSFORM	struct s_rttransform
# define CAST_RETURN	struct s_cast_return
# define UPVEC			(VEC3){0, 1, 0}
# define MAX_REFL		3
# define MAX_REFR		3
# define MAX_AREA		64
# define SAMPLING		1
# define WINDOW_SIZE	(t_point2){1024, 768}
# define BUFFER_SIZE	(t_point2){WINDOW_SIZE.x * SAMPLING, WINDOW_SIZE.y * SAMPLING}
# define CCLEAR_VALUE	0
# define FCLEAR_VALUE	0
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2
# define DIFFUSE		oren_nayar_diffuse
# define SPECULAR		ggx_specular
# define RENDER_NORMALS	false

typedef struct	s_rttransform
{
	RTTRANSFORM	*parent;
	RTTRANSFORM	*target;
	TRANSFORM	current;
}				t_rttransform;

typedef struct	s_light
{
	RTTRANSFORM	*target;
	UCHAR		type;
	UCHAR		cast_shadow;
	float		power;
	float		attenuation;
	float		falloff;
	float		spot_size;
	float		ambient_coef;
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
	void		*alpha_map;
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
	RTTRANSFORM	*transform;
	MATERIAL	*material;
	PRIMITIVE	prim;
}				t_rtprim;

typedef struct	s_camera
{
	RTTRANSFORM	*transform;
	float		fov;
	float		znear;
	float		zfar;
	RAY			ray;
	MAT4		m4_view;
}				t_camera;

typedef struct	s_scene
{
	float		bloom_intensity;
	float		bloom_radius;
	float		bloom_threshold;
	ARRAY		primitives;
	ARRAY		lights;
	CAMERA		*active_camera;
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
	VEC2		uv;
	RAY			ray;
	INTERSECT	intersect;
	MAT3		tbn;
	MATERIAL	mtl;
}				t_cast_return;

typedef struct	s_engine_opt
{
	UINT		max_refr;
	UINT		max_refl;
	UINT		area_sampling;
	t_point2	window_size;
	t_point2	internal_size;
}				t_engine_opt;

typedef struct	s_pixel_callback
{
	void		*arg;
	void		(*function)(void *arg, t_point2 coord);
}				t_pixel_callback;

typedef struct	s_engine
{
	BOOL		stop_rendering;
	UINT		max_refr;
	UINT		max_refl;
	UINT		refl_iteration;
	UINT		refr_iteration;
	UINT		area_sampling;
	void		*framework;
	void		*window;
	void		*image;
	void		*loading_screen;
	SCENE		*active_scene;
	void		(*progress_callback)(ENGINE*, float);
	INTERSECT	(*inter_functions[10])(OBJ, RAY, TRANSFORM*);
	VEC2		(*uv_functions[10])(OBJ, INTERSECT, TRANSFORM*);
	Uint32		last_time;
	ARRAY		post_treatments;
	FRAMEBUFFER	framebuffer;
	FRAMEBUFFER	finalbuffer;
	FRAMEBUFFER	positionbuffer;
	FRAMEBUFFER	normalbuffer;
	FRAMEBUFFER	mtlbuffer;
	FRAMEBUFFER	depthbuffer;
	SCENE		scene;
	VEC2		poisson_disc[64];
}				t_engine;

FRAMEBUFFER		new_framebuffer(TYPE type, t_point2 size, Uint8 depth);
SCENE			new_scene(void);
ENGINE			new_engine(t_engine_opt options);
void			print_progress(ENGINE *engine, float progress);
void			put_pixel_to_buffer(FRAMEBUFFER buffer,
				t_point2 coord, VEC4 color);
void			put_value_to_buffer(FRAMEBUFFER buffer,
				t_point2 coord, float value);
void			*get_buffer_value(FRAMEBUFFER buffer,
				t_point2 coord);
void			display_framebuffer(FRAMEBUFFER buffer, void *image);
void			copy_framebuffer(FRAMEBUFFER f1, FRAMEBUFFER f2);
void			generate_poisson_disc(VEC2 *disc, UINT disc_size, float min_dist, VEC2 limits);
float			frand_a_b(float a, float b);

/*
** Post treatment functions
*/
void			gamma_correction(ENGINE *engine, t_point2 coord);
void			depth_of_field(ENGINE *engine, t_point2 coord);
void			bloom(ENGINE *engine, t_point2 coord);
BOOL			do_post_treatment(ENGINE *engine, t_callback *callback);

VEC2			sphere_uv(u_obj sphere, INTERSECT inter, TRANSFORM *transform);
VEC2			cylinder_uv(u_obj cylinder, INTERSECT inter, TRANSFORM *transform);
VEC2			plane_uv(u_obj plane, INTERSECT inter, TRANSFORM *transform);
VEC3			sample_texture(void *image, VEC2 uv);
VEC3			sample_texture_filtered(void *image, VEC2 uv);
VEC2			sample_height_map(void *height_map, CAST_RETURN *ret);
VEC3			sample_normal_map(void *normal_map, CAST_RETURN *ret);


CAST_RETURN		cast_ray(ENGINE *engine, SCENE *scene, RAY ray);
CAST_RETURN		cast_light_ray(ENGINE *engine, SCENE *scene, RAY ray);
void			get_ret_mtl(CAST_RETURN	*ret);
VEC3			compute_lighting(ENGINE *engine, CAST_RETURN *ret);
VEC3			compute_refraction(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray, float aior);
VEC3			compute_reflection(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray);

void			destroy_scene(SCENE *scene);
void			destroy_engine(ENGINE *engine);

RTTRANSFORM		*new_rttransform(SCENE *scene, VEC3 position, VEC3 rotation, VEC3 scale);
RTPRIMITIVE		*new_rtprim(SCENE *scene);
MATERIAL		*new_material(SCENE *scene, char *name);
CAMERA			*new_camera(SCENE *scene, float fov, float znear, float zfar);
LIGHT			*new_light(SCENE *scene, UCHAR type, VEC3 position);
void			update_rttransform(RTTRANSFORM *transform);

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
MATERIAL		*mtl_stained_glass(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_rock_waterworn(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_metal_floor(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_skin(ENGINE *engine, SCENE *scene);
MATERIAL		*mtl_mirror(ENGINE *e, SCENE *s);

void			clear_renderer(ENGINE *engine);
void			clear_buffers(ENGINE *engine);
void			clear_uchar_bits(void *pixel);
void			clear_float_bits(void *pixel);
void			print_progress(ENGINE *engine, float progress);

/*
** Light calculation functions
*/

float			ggx_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, MATERIAL *mtl);
float			trowbridge_reitz_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, MATERIAL *mtl);
float			blinn_phong_specular(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl *mtl);
float			oren_nayar_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl *mtl);
float			lambert_diffuse(VEC3 normal, VEC3 eye,
				VEC3 lightdir, t_mtl *mtl);
VEC3			compute_lightdir(t_light l, VEC3 position);
VEC3			compute_point_color(LIGHT l, MATERIAL mtl,
				INTERSECT inter, RAY ray);

#endif