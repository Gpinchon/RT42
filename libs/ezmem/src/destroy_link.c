/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:40:25 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/21 11:59:09 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void	destroy_ezlink(LINK *ezlink)
{
	if (!ezlink)
		return ;
	destroy_ezarray(&ezlink->array);
	if (ezlink->prev)
		ezlink->prev->next = ezlink->next;
	if (ezlink->next)
		ezlink->next->prev = ezlink->prev;
	free(ezlink);
}

void	destroy_ezchain(LINK *from)
{
	if (from)
	{
		destroy_ezchain(from->next);
		destroy_ezlink(from);
	}
}
