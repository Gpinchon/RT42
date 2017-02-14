/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:07:35 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/10 18:10:28 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat2	mat2_shear_x(float amount)
{
	return ((t_mat2){.m = {
		1, amount,
		0, 1
	}});
}

t_mat2	mat2_shear_y(float amount)
{
	return ((t_mat2){.m = {
		1, 0,
		amount, 1
	}});
}
