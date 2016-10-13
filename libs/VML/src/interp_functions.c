/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interp_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:41:14 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 19:00:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	lerp(float start, float end, float percent)
{
	return (percent * (end - start) + start);
}

float	cubic(float start, float end, float percent)
{
	percent = (percent * percent) * (3.f - (2.f * percent));
	return (lerp(start, end, percent));
}
