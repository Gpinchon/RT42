/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:10:48 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:03:39 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

inline t_mat2		mat2_minors(const t_mat2 m)
{
	return ((t_mat2){.m = {
		m.m[3], m.m[2],
		m.m[1], m.m[0]
	}});
}

inline t_mat3		mat3_minors(const t_mat3 m)
{
	t_mat3	r;

	r.m[0] = mat2_determinant((t_mat2){.m = {m.m[4], m.m[5], m.m[7], m.m[8]}});
	r.m[1] = mat2_determinant((t_mat2){.m = {m.m[3], m.m[5], m.m[6], m.m[8]}});
	r.m[2] = mat2_determinant((t_mat2){.m = {m.m[3], m.m[4], m.m[6], m.m[7]}});
	r.m[3] = mat2_determinant((t_mat2){.m = {m.m[1], m.m[2], m.m[7], m.m[8]}});
	r.m[4] = mat2_determinant((t_mat2){.m = {m.m[0], m.m[2], m.m[6], m.m[8]}});
	r.m[5] = mat2_determinant((t_mat2){.m = {m.m[0], m.m[1], m.m[6], m.m[7]}});
	r.m[6] = mat2_determinant((t_mat2){.m = {m.m[1], m.m[2], m.m[4], m.m[5]}});
	r.m[7] = mat2_determinant((t_mat2){.m = {m.m[0], m.m[2], m.m[3], m.m[5]}});
	r.m[8] = mat2_determinant((t_mat2){.m = {m.m[0], m.m[1], m.m[3], m.m[4]}});
	return (r);
}

inline static void	mat4_minors1(t_mat4 *r, t_mat4 m)
{
	r->m[8] = mat3_determinant((t_mat3){.m = {m.m[1], m.m[2], m.m[3],
		m.m[5], m.m[6], m.m[7], m.m[13], m.m[14], m.m[15]}});
	r->m[9] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[2], m.m[3],
		m.m[4], m.m[6], m.m[7], m.m[12], m.m[14], m.m[15]}});
	r->m[10] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[3],
		m.m[4], m.m[5], m.m[7], m.m[12], m.m[13], m.m[15]}});
	r->m[11] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[2],
		m.m[4], m.m[5], m.m[6], m.m[12], m.m[13], m.m[14]}});
	r->m[12] = mat3_determinant((t_mat3){.m = {m.m[1], m.m[2], m.m[3],
		m.m[5], m.m[6], m.m[7], m.m[9], m.m[10], m.m[11]}});
	r->m[13] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[2], m.m[3],
		m.m[4], m.m[6], m.m[7], m.m[8], m.m[10], m.m[11]}});
	r->m[14] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[3],
		m.m[4], m.m[5], m.m[7], m.m[8], m.m[9], m.m[11]}});
	r->m[15] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[2],
		m.m[4], m.m[5], m.m[6], m.m[8], m.m[9], m.m[10]}});
}

inline t_mat4		mat4_minors(const t_mat4 m)
{
	t_mat4	r;

	r.m[0] = mat3_determinant((t_mat3){.m = {m.m[5], m.m[6], m.m[7],
		m.m[9], m.m[10], m.m[11], m.m[13], m.m[14], m.m[15]}});
	r.m[1] = mat3_determinant((t_mat3){.m = {m.m[4], m.m[6], m.m[7],
		m.m[8], m.m[10], m.m[11], m.m[12], m.m[14], m.m[15]}});
	r.m[2] = mat3_determinant((t_mat3){.m = {m.m[4], m.m[5], m.m[7],
		m.m[8], m.m[9], m.m[11], m.m[12], m.m[13], m.m[15]}});
	r.m[3] = mat3_determinant((t_mat3){.m = {m.m[4], m.m[5], m.m[6],
		m.m[8], m.m[9], m.m[10], m.m[12], m.m[13], m.m[14]}});
	r.m[4] = mat3_determinant((t_mat3){.m = {m.m[1], m.m[2], m.m[3],
		m.m[9], m.m[10], m.m[11], m.m[13], m.m[14], m.m[15]}});
	r.m[5] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[2], m.m[3],
		m.m[8], m.m[10], m.m[11], m.m[12], m.m[14], m.m[15]}});
	r.m[6] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[3],
		m.m[8], m.m[9], m.m[11], m.m[12], m.m[13], m.m[15]}});
	r.m[7] = mat3_determinant((t_mat3){.m = {m.m[0], m.m[1], m.m[2],
		m.m[8], m.m[9], m.m[10], m.m[12], m.m[13], m.m[14]}});
	mat4_minors1(&r, m);
	return (r);
}
