/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:24:55 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/04 13:30:47 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static char	point_is_too_close(VEC2 p, VEC2 *d, UINT dsize, float mdist, int *grid)
{
	UINT	i;

	i = 0;
	while (i < dsize)
	{
		if (grid[i] && vec2_distance(p, d[i]) < mdist)
			return (true);
		i++;
	}
	return (false);
}

static VEC2	new_point_around(float mdist, VEC2 p, VEC2 limits)
{
	float	radius;
	float	angle;

	radius = (frand_a_b(limits.x, limits.y) + 1) * mdist;
	angle = 2 * M_PI * frand_a_b(limits.x, limits.y);
	p = new_vec2(
		cos(angle) * radius + p.x,
		sin(angle) * radius + p.y);
	return (p);
}

float	frand_a_b(float a, float b)
{
	return ((rand() / (float)RAND_MAX) * (b - a) + a);
}


void		generate_poisson_disc(VEC2 *d, UINT dsize, float mdist, VEC2 limits)
{
	UINT	i;
	UINT	index;
	UINT	attempts;
	int		grid[dsize];
	VEC2	p;

	i = 1;
	memset(grid, -1, dsize * sizeof(int));
	srand(time(NULL));
	p.x = frand_a_b(limits.x, limits.y);
	p.y = frand_a_b(limits.x, limits.y);
	d[0] = p;
	grid[0] = 1;
	while (i < dsize)
	{
		attempts = 0;
		index = frand_a_b(0, dsize);
		if (grid[index] == -1)
			while (attempts < 1000000)
			{
				p = new_point_around(mdist, p, limits);
				if (!point_is_too_close(p, d, dsize, mdist, grid)
				&& p.x >= limits.x && p.x <= limits.y
				&& p.y >= limits.x && p.y <= limits.y)
				{
					d[index] = p;
					grid[index] = 1;
					i++;
					break ;
				}
				attempts++;
			}
		if (attempts >= 1000000)
		{
			generate_poisson_disc(d, dsize, mdist, limits);
			return ;
		}
	}
	i = 0;
}
