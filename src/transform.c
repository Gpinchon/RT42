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

void	update_rttransform(RTTRANSFORM *t)
{
	if (!t || t->current.updated)
		return ;
	if (t->target)
		transform_set_target(&t->current, &t->target->current);
	if (t->parent)
		transform_set_parent(&t->current, &t->parent->current);
	t->current.updated = vmltrue;
}
