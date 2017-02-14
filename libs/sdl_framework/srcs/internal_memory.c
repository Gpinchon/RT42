/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 13:15:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/06 18:55:06 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void		*int_memset(void *str, int c, size_t n)
{
	unsigned char	*buffer;

	buffer = str;
	while (n != 0)
	{
		*buffer++ = c;
		n--;
	}
	return (str);
}

void		*int_memalloc(size_t size)
{
	void	*memalloc;

	if (!size || !(memalloc = malloc(size)))
		return (NULL);
	int_memset(memalloc, '\0', size);
	return (memalloc);
}
