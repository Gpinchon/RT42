/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VML.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 17:13:36 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/12 18:11:46 by gpinchon         ###   ########.fr       */
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


#endif