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

/*static char	point_is_too_close(VEC2 p, VEC2 *disc, UINT disc_size, UINT index, float min_dist)
{
	UINT	i;
	UINT	min;
	UINT	max;
	float	minsqr;
	
	min = index <= 2 ? 0 : index - 2;
	//max = index >= disc_size - 2 ? disc_size : index + 2;
	max = index;
	i = min;
	minsqr = sqrt(min_dist);
	while (i < max)
	{
		if (vec2_distance(p, disc[i]) < minsqr)
			return (true);
		i++;
	}
	return (false);
	(void)disc_size;
}*/

static char	point_is_too_close(VEC2 p, VEC2 *disc, UINT disc_size, float min_dist, int *grid)
{
	UINT	i;

	i = 0;
	while (i < disc_size)
	{
		if (grid[i] && vec2_distance(p, disc[i]) < min_dist)
			return (true);
		i++;
	}
	return (false);
}

#include <time.h>


static VEC2	new_point_around(float min_dist, VEC2 p, VEC2 limits)
{
	float	radius;
	float	angle;

	radius = (frand_a_b(limits.x, limits.y) + 1) * min_dist;
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


void		generate_poisson_disc(VEC2 *disc, UINT disc_size, float min_dist, VEC2 limits)
{
	UINT	i;
	UINT	index;
	UINT	attempts;
	int		grid[disc_size];
	VEC2	p;

	i = 1;
	memset(grid, -1, disc_size * sizeof(int));
	srand(time(NULL));
	p.x = frand_a_b(limits.x, limits.y);
	p.y = frand_a_b(limits.x, limits.y);
	//p = new_vec2(frand_a_b(limits.x, limits.y), frand_a_b(limits.x, limits.y));//new_point_around(min_dist);
	disc[0] = p;
	grid[0] = 1;
	while (i < disc_size)
	{
		attempts = 0;
		index = frand_a_b(0, disc_size);
		if (grid[index] == -1)
			while (attempts < 1000000)
			{
				p = new_point_around(min_dist, p, limits);
				if (!point_is_too_close(p, disc, disc_size, min_dist, grid)
				&& p.x >= limits.x && p.x <= limits.y
				&& p.y >= limits.x && p.y <= limits.y)
				{
					disc[index] = p;
					grid[index] = 1;
					i++;
					break ;
				}
				attempts++;
			}
		if (attempts >= 1000000)
		{
			generate_poisson_disc(disc, disc_size, min_dist, limits);
			return ;
		}
	}
	i = 0;
	while (i < disc_size)
	{
		printf("%i : %f, %f\n", i, disc[i].x, disc[i].y);
		i++;
	}
}
