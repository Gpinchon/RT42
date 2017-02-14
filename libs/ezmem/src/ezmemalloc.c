/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezmemalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 11:07:41 by anonymous         #+#    #+#             */
/*   Updated: 2016/11/21 11:15:38 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void	*ezmemalloc(UINT size)
{
	char	*memptr;

	memptr = malloc(size);
	while (size)
	{
		size--;
		memptr[size] = 0;
	}
	return (memptr);
}
