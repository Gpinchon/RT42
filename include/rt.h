/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/14 17:06:36 by gpinchon         ###   ########.fr       */
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
# define P2				struct s_point2
# define UPVEC			(VEC3){0, 1, 0}
# define MAX_REFL		3
# define MAX_REFR		3
# define MAX_AREA		64
# define SAMPLING		1
# define WINDOW_SIZE	(t_point2){1024, 768}
# define BUFFER_X		WINDOW_SIZE.x * SAMPLING
# define BUFFER_Y		WINDOW_SIZE.y * SAMPLING
# define BUFFER_SIZE	(t_point2){BUFFER_X, BUFFER_Y}
# define CCLEAR_VALUE	0
# define FCLEAR_VALUE	0
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2
# define DIFFUSE		oren_nayar_diffuse
# define SPECULAR		ggx_specular
# define RENDER_NORMALS	false
# define NUMTHREADS		16
# define DIV_THREADS	4

typedef struct s_rttransform	t_rttransform;

struct							s_rttransform
{
	t_rttransform	*parent;
	t_rttransform	*target;
	TRANSFORM		current;
};

typedef struct					s_light
{
	t_rttransform	*target;
	UCHAR			type;
	UCHAR			cast_shadow;
	float			power;
	float			attenuation;
	float			falloff;
	float			spot_size;
	float			ambient_coef;
	VEC3			color;
	VEC3			position;
	VEC3			direction;
}								t_light;

# pragma pack(push, 1)

typedef struct					s_mtl
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
}								t_mtl;

typedef struct					s_rtprim
{
	UCHAR			transformed;
	t_rttransform	*transform;
	t_mtl			*material;
	PRIMITIVE		prim;
}								t_rtprim;

typedef struct					s_cast_return
{
	VEC2		uv;
	RAY			ray;
	INTERSECT	intersect;
	MAT3		tbn;
	MATERIAL	mtl;
}								t_cast_return;

# pragma pack(pop)

typedef struct					s_camera
{
	t_rttransform	*transform;
	float			fov;
	float			znear;
	float			zfar;
	RAY				ray;
	MAT4			m4_view;
}								t_camera;

typedef struct					s_scene
{
	float		bloom_intensity;
	float		bloom_radius;
	float		bloom_threshold;
	ARRAY		primitives;
	ARRAY		lights;
	t_camera	*active_camera;
	t_ezlink	*cameras;
	t_ezlink	*transforms;
	t_ezlink	*materials;
}								t_scene;

typedef struct					s_framebuffer
{
	Uint8		bpp;
	Uint8		opp;
	UINT		sizeline;
	t_point2	size;
	ARRAY		array;
}								t_framebuffer;

typedef struct					s_engine_opt
{
	UINT		max_refr;
	UINT		max_refl;
	UINT		area_sampling;
	t_point2	window_size;
	t_point2	internal_size;
}								t_engine_opt;

typedef struct					s_pixel_callback
{
	void		*arg;
	void		(*function)(void *arg, t_point2 coord);
}								t_pixel_callback;

typedef struct					s_engine
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
	t_scene		*active_scene;
	void		(*progress_callback)(ENGINE *engine, float a);
	INTERSECT	(*inter_functions[10])(OBJ obj, RAY ray, TRANSFORM *trans);
	VEC2		(*uv_functions[10])(OBJ obj, INTERSECT inter, TRANSFORM *trans);
	Uint32		last_time;
	ARRAY		post_treatments;
	FRAMEBUFFER	framebuffer;
	FRAMEBUFFER	finalbuffer;
	FRAMEBUFFER	hdrbuffer;
	FRAMEBUFFER	positionbuffer;
	FRAMEBUFFER	normalbuffer;
	FRAMEBUFFER	depthbuffer;
	t_scene		scene;
	VEC2		poisson_disc[64];
}								t_engine;

typedef struct	s_pdisc
{
	t_vec2	point;
	t_vec2	*disc;
	UINT	dsize;
	float	mdist;
	int		*grid;
	t_vec2	limits;
}				t_pdisc;

typedef struct					s_pth_args
{
	t_engine	*engine;
	t_scene		*scene;
	BOOL		area_lights;
	t_point2	scoord;
	t_point2	limit;
}								t_pth_args;

FRAMEBUFFER						new_framebuffer(TYPE type,
										t_point2 size, Uint8 depth);
SCENE							new_scene(void);
ENGINE							new_engine(t_engine_opt options);
void							print_progress(ENGINE *engine, float progress);
void							put_pixel_to_buffer(FRAMEBUFFER buffer,
								t_point2 coord, VEC4 color);
void							put_value_to_buffer(FRAMEBUFFER buffer,
								t_point2 coord, float value);
void							*get_buffer_value(FRAMEBUFFER buffer,
								t_point2 coord);
void							display_framebuffer(FRAMEBUFFER buf, void *im);
void							copy_framebuffer(FRAMEBUFFER f, FRAMEBUFFER f2);
void							generate_poisson_disc(VEC2 *disc, UINT discize,
											float min_dist, VEC2 limits);
float							frand_a_b(float a, float b);

/*
** Post treatment functions
*/
void							gamma_correction(ENGINE *eng, t_point2 coord);
void							depth_of_field(ENGINE *eng, t_point2 coord);
void							bloom(ENGINE *eng, t_point2 coord);
void							ssao(ENGINE *eng, t_point2 coord);
VEC4							blur_sample(ENGINE *eng, t_point2 c,
														float intensity);
VEC4							blur_sample_with_threshold(ENGINE *eng,
								t_point2 p, float intensity, float threshold);
BOOL							do_post_treatment(ENGINE *eng, t_callback *cb);

VEC2							triangle_uv(t_obj tri, INTERSECT inter,
														TRANSFORM *transform);
VEC2							sphere_uv(t_obj sphere, INTERSECT inter,
														TRANSFORM *transform);
VEC2							cylinder_uv(t_obj cyli, INTERSECT inter,
														TRANSFORM *transform);
VEC2							plane_uv(t_obj plane, INTERSECT inter,
														TRANSFORM *transform);
VEC3							sample_texture(void *image, VEC2 uv);
VEC3							sample_texture_filtered(void *image, VEC2 uv);
VEC2							sample_height_map(void *height_map,
														CAST_RETURN *ret);
VEC3							sample_normal_map(void *normal_map,
														CAST_RETURN *ret);

CAST_RETURN						cast_ray(ENGINE *eng, SCENE *sc, RAY ray);
CAST_RETURN						cast_light_ray(ENGINE *eng, SCENE *sc, RAY ray);
void							get_ret_mtl(CAST_RETURN	*ret);
VEC3							compute_lighting(ENGINE *eng, CAST_RETURN *ret);
VEC3							compute_refraction(ENGINE *e, CAST_RETURN *ret,
												RAY *cur_ray, float aior);
VEC3							compute_reflection(ENGINE *e,
									CAST_RETURN *ret, RAY *cur_ray);

void							destroy_scene(SCENE *sc);
void							destroy_engine(ENGINE *eng);

t_rttransform					*new_rttransform(SCENE *sc, VEC3 pos,
											VEC3 rot, VEC3 scale);
RTPRIMITIVE						*new_rtprim(SCENE *sc);
MATERIAL						*new_material(SCENE *sc, char *name);
t_camera						*new_camera(SCENE *sc, float fov,
													float znear, float zfar);
LIGHT							*new_light(SCENE *sc, UCHAR type, VEC3 pos);
void							update_rttransform(t_rttransform *transform);

MATERIAL						*get_mtl_by_name(SCENE *sc, char *name);
MATERIAL						*mtl_aquamarine(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_greasy_metal(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_rusted_metal(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_rock_copper(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_rock_sliced(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_granite(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_water(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_brick(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_harshbricks(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_octostone(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_scuffed_plastic_red(ENGINE *en, SCENE *sc);
MATERIAL						*mtl_scuffed_aluminium(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_stained_glass(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_rock_waterworn(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_metal_floor(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_skin(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_mirror(ENGINE *e, SCENE *s);
MATERIAL						*mtl_light(ENGINE *eng, SCENE *sc);
MATERIAL						*mtl_cube(ENGINE *e, SCENE *s);

BOOL							render_scene(ENGINE *e, SCENE *sc);
void							*render_part(void *pth_args);
void							fill_buffers(ENGINE *en, t_point2 screen_c,
													CAST_RETURN *ret);
VEC3							compute_area_lighting(ENGINE *eng,
													CAST_RETURN *ret);
BOOL							scene_contains_area_light(SCENE *sc);

void							clear_renderer(ENGINE *eng);
void							clear_buffers(ENGINE *eng);
void							clear_uchar_bits(void *pixel);
void							clear_float_bits(void *pixel);
void							print_progress(ENGINE *eng, float progress);

/*
** Light calculation functions
*/

float							ggx_specular(VEC3 normal, VEC3 eye,
								VEC3 lightdir, MATERIAL *mtl);
float							trowbridge_reitz_specular(VEC3 normal, VEC3 eye,
								VEC3 lightdir, MATERIAL *mtl);
float							blinn_phong_specular(VEC3 normal, VEC3 eye,
								VEC3 lightdir, t_mtl *mtl);
float							oren_nayar_diffuse(VEC3 normal, VEC3 eye,
								VEC3 lightdir, t_mtl *mtl);
float							lambert_diffuse(VEC3 normal, VEC3 eye,
								VEC3 lightdir, t_mtl *mtl);
VEC3							compute_lightdir(t_light l, VEC3 position);
VEC3							compute_point_color(LIGHT l, MATERIAL mtl,
								INTERSECT inter, RAY ray);

#endif
