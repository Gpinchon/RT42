/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interp_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:41:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:52:07 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

float	interp_linear(float start, float end, float percent)
{
	return (percent * (end - start) + start);
}

float	interp_cubic(float start, float end, float percent)
{
	percent = (percent * percent) * (3.f - (2.f * percent));
	return (interp_linear(start, end, percent));
}

float	interp_clamp(float start, float end, float percent)
{
	return (CLAMP(percent, start, end));
}

float	interp_cycle(float start, float end, float percent)
{
	return (CYCLE(percent, start, end));
}
