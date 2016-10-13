/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VML.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 17:13:36 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 16:40:55 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VML_H
# define VML_H

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;


typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_mat4
{
	float		m[16];
}				t_mat4;

typedef struct	s_mat3
{
	float		m[9];
}				t_mat3;

t_vec3	vec3_add_vec3(t_vec3 v, t_vec3 v1);
t_vec4	vec4_add_vec4(t_vec4 v, t_vec4 v1);
t_vec3	vec4_to_vec3(t_vec4 v);
t_vec4	vec3_to_vec4(t_vec3 v);
t_vec3	vec3_cross_vec3(t_vec3 v, t_vec3 v1);
float	vec3_dot(t_vec3 v1, t_vec3 v2);
float	vec4_dot(t_vec4 v1, t_vec4 v2);
float	vec3_length(t_vec3 v);
float	vec4_length(t_vec4 v);
t_vec3	vec3_mult_vec3(t_vec3 v1, t_vec3 v2);
t_vec4	vec4_mult_vec4(t_vec4 v1, t_vec4 v2);
t_vec3	mat4_mult_vec3(t_mat4 m, t_vec3 v);
t_vec4	mat4_mult_vec4(t_mat4 m, t_vec4 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec4	vec4_normalize(t_vec4 v);
t_vec3	vec3_sub_vec3(t_vec3 v, t_vec3 v1);
t_vec4	vec4_sub_vec4(t_vec4 v, t_vec4 v1);

t_mat4	mat4_identity(void);
t_mat4	mat4_zero(void);
t_mat3	mat3_identity(void);
t_mat3	mat3_zero(void);
t_mat3	mat4_to_mat3(t_mat4 m);
t_mat4	mat3_to_mat4(t_mat3 m);
t_mat4	mat4_inverse(const t_mat4 i);
t_mat4	mat4_transpose(const t_mat4 in);
t_mat4	mat4_mult_mat4(t_mat4 m, t_mat4 m1);


#endif