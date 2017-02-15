/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vml_memset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 23:09:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/23 23:42:33 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*vml_memset(void *dst, int c, unsigned int n)
{
	char	*d;

	if (dst && n)
	{
		d = dst;
		while (n--)
		{
			d[n] = c;
		}
	}
	return (dst);
}