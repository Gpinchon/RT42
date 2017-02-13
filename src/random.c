/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:24:55 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 18:31:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static char	point_is_too_close(VEC2 p, VEC2 *d, UINT dsize,
	float mdist, int *grid)
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

inline float	frand_a_b(float a, float b)
{
	return ((random() / (float)RAND_MAX) * (b - a) + a);
}

static VEC2		new_point_around(float mdist, VEC2 p, VEC2 limits)
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

void			generate_poisson_disc(VEC2 *d, UINT dsize, float mdist,
		VEC2 l)
{
	UINT	i;
	UINT	index;
	UINT	attempts;
	int		g[dsize];
	VEC2	p;

	i = 1;
	memset(g, 0, dsize * sizeof(int));
	srandom(time(NULL));
	p = new_vec2(frand_a_b(l.x, l.y), frand_a_b(l.x, l.y));
	d[0] = p;
	g[0] = 1;
	while (i < dsize)
	{
		attempts = 0;
		if (!g[(index = frand_a_b(0, dsize))])
			while (++attempts < 1000000)
			{
				p = new_point_around(mdist, p, l);
				if ((g[index] = (!point_is_too_close(p, d, dsize, mdist, g)
				&& p.x >= l.x && p.x <= l.y && p.y >= l.x && p.y <= l.y)))
				{
					d[index] = p;
					i++;
					break ;
				}
			}
		if (attempts >= 1000000)
		{
			generate_poisson_disc(d, dsize, mdist, l);
			return ;
		}
	}
}
