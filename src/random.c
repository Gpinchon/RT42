/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:24:55 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 19:30:55 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static char		point_is_too_close(t_pdisc ds)
{
	UINT	i;

	i = 0;
	while (i < ds.dsize)
	{
		if (ds.grid[i] && vec2_distance(ds.point, ds.disc[i]) < ds.mdist)
			return (true);
		i++;
	}
	return (false);
}

inline float	frand_a_b(float a, float b)
{
	return ((random() / (float)RAND_MAX) * (b - a) + a);
}

static t_vec2	new_point_around(float mdist, t_vec2 p, t_vec2 limits)
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

int				generate_point(t_pdisc ds)
{
	UINT	attempts;
	UINT	index;

	attempts = 0;
	if (!ds.grid[(index = frand_a_b(0, ds.dsize))])
		while (++attempts < 1000000)
		{
			ds.point = new_point_around(ds.mdist, ds.point, ds.limits);
			if ((ds.grid[index] = (!point_is_too_close(ds)
			&& ds.point.x >= ds.limits.x && ds.point.x <= ds.limits.y
			&& ds.point.y >= ds.limits.x && ds.point.y <= ds.limits.y)))
			{
				ds.disc[index] = ds.point;
				return (1);
			}
		}
	if (attempts >= 1000000)
		return (-1);
	return (0);
}

void			generate_poisson_disc(t_vec2 *d, UINT dsize, float mdist,
		t_vec2 l)
{
	int		g[dsize];
	t_vec2	p;
	int		r;
	UINT	i;

	i = 1;
	memset(g, 0, dsize * sizeof(int));
	srandom(time(NULL));
	p = new_vec2(frand_a_b(l.x, l.y), frand_a_b(l.x, l.y));
	d[0] = p;
	g[0] = 1;
	while (i < dsize)
	{
		if ((r = generate_point((t_pdisc){p, d, dsize, mdist, g, l})) == 1)
			i++;
		else if (r == -1)
		{
			generate_poisson_disc(d, dsize, mdist, l);
			return ;
		}
	}
}
