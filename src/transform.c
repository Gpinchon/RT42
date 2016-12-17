/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:55:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 22:53:02 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	update_transform(TRANSFORM *transform)
{
	VEC3	direction;

	if (!transform || transform->updated)
		return ;
	if (transform->target)
	{
		direction = vec3_normalize(vec3_sub(transform->target->position, transform->position));
		transform->rotation = (VEC3){asin(direction.y), -atan2(direction.x, direction.z), transform->rotation.z};
	}
	transform->translate = mat4_translate(transform->position);
	transform->rotate = mat4_rotation(transform->rotation);
	transform->scale = mat4_scale(transform->scaling);
	transform->matrix = mat4_combine(transform->translate, transform->rotate, transform->scale);
	transform->updated = true;
}
