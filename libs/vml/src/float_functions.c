/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:03:47 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:51:40 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

float	fract(float f)
{
	return (f - (int)f);
}

char	float_equal(float a, float b)
{
	return (fabs(a - b) <= FLOAT_ZERO);
}
