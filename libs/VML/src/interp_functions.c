/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interp_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:41:14 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 18:58:27 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

float	lerp(float start, float end, float percent)
{
	return (percent * (end - start) + start);
}

float	cubic(float start, float end, float percent)
{
	percent = pow(percent, 2) * (3.f - (2.f * percent));
	return (lerp(start, end, percent));
}
