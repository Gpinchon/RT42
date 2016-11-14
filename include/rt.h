/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/14 21:44:56 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework.h>
# include <vml.h>
# include <ezmem.h>
# define ENGINE			struct s_engine
# define FRAMEBUFFER	struct s_framebuffer
# define LIGHT			struct s_light
# define SUPERSAMPLING	4
# define WINDOW_SIZE	(t_point2){512, 512}
# define WS				WINDOW_SIZE
# define BUFFER_SIZE	(t_point2){WS.x * SUPERSAMPLING, WS.y * SUPERSAMPLING}
# define DIRECTIONAL	0x0
# define SPOT			0x1
# define POINT			0x2

typedef struct	s_light
{
	UCHAR	type;
	float	power;
	float	attenuation;
	float	falloff;
	float	spot_size;
	t_rgb	color;
	t_vec3	position;
	t_vec3	direction;
}				t_light;

typedef struct	s_mtl
{
	VEC3		base_color;
	float		roughness;
	float		metallic;
	float		specular;
	float		alpha;
}				t_mtl;

typedef struct	s_scene
{
	UINT		primitive_nbr;
	UINT		light_nbr;
	UINT		mtl_nbr;
	PRIMITIVE	*primitive;
	LIGHT		*light;
}				t_scene;

typedef struct	s_framebuffer
{
	Uint8		bpp;
	UINT		sizeline;
	ARRAY		array;
	t_point2	size;
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
}				t_engine;

#endif