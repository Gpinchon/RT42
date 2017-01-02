/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:24:55 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/27 22:04:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static char	point_is_too_close(VEC2 p, VEC2 *disc, UINT disc_size, UINT index, float min_dist)
{
	UINT	i;
	UINT	min;
	UINT	max;

	
	min = index <= 2 ? 0 : index - 2;
	max = index >= disc_size - 2 ? disc_size : index + 2;
	i = min;
	while (i < max + 2)
	{
		if (vec2_distance(p, disc[i]) < min_dist)
			return (true);
		i++;
	}
	return (false);
}

static VEC2	new_point_around(float min_dist, VEC2 p)
{
	float	radius;
	float	angle;

	radius = frand_a_b(0, min_dist) + min_dist;
	angle = frand_a_b(0, 2 * M_PI);
	p = new_vec2(
		p.x + cos(angle) * radius,
		p.y + sin(angle) * radius);
	return (p);
}

float	frand_a_b(float a, float b)
{
	return ((rand()/(float)RAND_MAX) * (b-a) + a);
}

void		generate_poisson_disc(VEC2 *disc, UINT disc_size, float min_dist, VEC2 limits)
{
	UINT	i;
	UINT	attempts;
	VEC2	p;

	i = 1;
	p = new_vec2(frand_a_b(limits.x, limits.y), frand_a_b(limits.x, limits.y));//new_point_around(min_dist);
	disc[0] = p;
	printf("%i : %f, %f\n", 0, disc[0].x, disc[0].y);
	while (i < disc_size)
	{
		attempts = 0;
		while (attempts < 100000)
		{
			p = new_point_around(min_dist, p);
			if (!point_is_too_close(p, disc, disc_size, i, min_dist)
			&& p.x >= limits.x && p.x <= limits.y
			&& p.y >= limits.x && p.y <= limits.y)
			{
				disc[i] = p;
				break ;
			}
			attempts++;
		}
		printf("%i : %f, %f\n", i, disc[i].x, disc[i].y);
		i++;
	}
}
