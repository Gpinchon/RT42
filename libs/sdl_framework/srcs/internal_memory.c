/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 13:15:45 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/02 13:17:10 by gpinchon         ###   ########.fr       */
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

	if (!(memalloc = malloc(size)) || !size)
		return (NULL);
	int_memset(memalloc, '\0', size);
	return (memalloc);
}
