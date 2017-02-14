/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:14:33 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/12 13:59:06 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

void	transform_update(TRANSFORM *transform)
{
	if (!transform)
		return ;
	transform->translate = mat4_translate(transform->position);
	transform->rotate = mat4_rotation(transform->rotation);
	transform->scale = mat4_scale(transform->scaling);
	transform->transform = mat4_combine(transform->translate,
		transform->rotate, transform->scale);
	transform->updated = vmltrue;
}

void	transform_set_target(TRANSFORM *transform, TRANSFORM *target)
{
	VEC3	direction;

	if (!transform || !target)
		return ;
	direction = vec3_normalize(vec3_sub(target->position, transform->position));
	transform->rotation = (VEC3){-asin(direction.y),
		atan2(direction.x, direction.z), transform->rotation.z};
	transform_update(transform);
}

void	transform_set_parent(TRANSFORM *transform, TRANSFORM *parent)
{
	if (!parent || !transform)
		return ;
	transform->transform = mat4_mult_mat4(parent->transform,
			transform->transform);
}
