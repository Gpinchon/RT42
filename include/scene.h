/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:16:20 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/13 18:40:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "parser.h"

typedef PRIMITIVE	(*t_cb_0)(void);
typedef PRIMITIVE	(*t_cb_1)(float radius);
typedef PRIMITIVE	(*t_cb_2)(float radius, float);
typedef PRIMITIVE	(*t_cb_3)(VEC3, VEC3, VEC3);

typedef struct s_objprim	t_objprim;
typedef enum e_typeargs		t_typeargs;

enum			e_typeargs
{
	args0 = 0x00,
	args1 = 0x01,
	args2 = 0x02,
	args3 = 0x03,
	args4 = 0x04
};

struct			s_objprim
{
	void		*fct;
	t_typeargs	args;
};

VEC3			get_vec3_json(t_value val);
VEC2			get_vec2_json(t_value val);

void			fill_camera(t_value val, void *engine);
void			fill_materials(t_value val, int id, void *obj);
void			fill_lights(t_value val, int i, void *obj);
void			fill_primitive(t_value val, int i, void *obj);
void			fill_mesh(t_value v, int i, void *obj);
void			fill_map(t_value val, ENGINE *engine, MATERIAL *mtl);

ENGINE			create_scene(t_value val);
t_objprim		get_fct_primitive(int id);
int				key_primitive(unsigned long id);
int				get_idfct(unsigned long *key, unsigned long val);
unsigned long	djb2(const char *str);
PRIMITIVE		create_primitive(t_value val, t_objprim prim);
VEC3			get_vec3_json(t_value val);

#endif
