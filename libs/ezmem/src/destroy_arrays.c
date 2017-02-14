/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 00:21:06 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/14 14:45:18 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void		destroy_ezarray(ARRAY *ezarray)
{
	if (ezarray->total_size)
		free(ezarray->data);
	*ezarray = (ARRAY){0, 0x000, 0, 0, NULL};
}

void		destroy_ezstring(STRING *str)
{
	destroy_ezarray(&str->array);
	str->length = 0;
	str->tostring = NULL;
}
