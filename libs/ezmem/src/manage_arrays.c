/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 00:21:55 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/14 14:45:30 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void		*ezarray_get_index(const ARRAY ezarray, const UINT index)
{
	return (index < ezarray.length
		&& ezarray.data ? ezarray.data + index * ezarray.data_size : NULL);
}

BOOL		ezarray_is_signed(const ARRAY ezarray)
{
	return (!(ezarray.type & 0x100));
}

void		ezarray_realloc(ARRAY *ezarray, UINT new_length)
{
	ezarray->length = new_length;
	ezarray->total_size = ezarray->length * ezarray->data_size;
	ezarray->data = realloc(ezarray->data, ezarray->total_size + 1);
	((char*)ezarray->data)[ezarray->total_size] = 0;
}
