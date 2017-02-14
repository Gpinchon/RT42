/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 00:20:43 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 10:41:27 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>
#include <data_size.h>
#include <stdarg.h>

static void	allocate_ezarray(ARRAY *ezarray, const TYPE dt,
	UINT l, va_list argptr)
{
	if ((dt & 0x00F) < 4)
		ezarray->data_size = g_datasize[(dt & 0x0F0) >> 4][dt & 0x00F];
	else
	{
		ezarray->data_size = va_arg(argptr, UINT);
		va_end(argptr);
	}
	ezarray->type = dt;
	ezarray->length = l;
	ezarray->total_size = ezarray->length * ezarray->data_size;
	ezarray->data = ezmemalloc(ezarray->total_size + 1);
}

static void	allocate_ezarray_dirty(ARRAY *ezarray, const TYPE dt,
	UINT l, va_list argptr)
{
	if ((dt & 0x00F) < 4)
		ezarray->data_size = g_datasize[(dt & 0x0F0) >> 4][dt & 0x00F];
	else
	{
		ezarray->data_size = va_arg(argptr, UINT);
		va_end(argptr);
	}
	ezarray->type = dt;
	ezarray->length = l;
	ezarray->total_size = ezarray->length * ezarray->data_size;
	ezarray->data = malloc(ezarray->total_size + 1);
}

ARRAY		new_ezarray(const TYPE datatype, UINT length, ...)
{
	ARRAY	ezarray;
	va_list	argptr;

	va_start(argptr, length);
	allocate_ezarray(&ezarray, datatype, length, argptr);
	length = ezarray.length;
	return (ezarray);
}

ARRAY		new_ezarray_dirty(const TYPE datatype, UINT length, ...)
{
	ARRAY	ezarray;
	va_list	argptr;

	va_start(argptr, length);
	allocate_ezarray_dirty(&ezarray, datatype, length, argptr);
	((char*)ezarray.data)[ezarray.total_size] = 0;
	return (ezarray);
}

STRING		new_ezstring(const char *src)
{
	STRING		str;
	const char	*ptr;
	void		*data;

	ptr = src;
	str.length = 0;
	while (*src)
	{
		str.length++;
		src++;
	}
	src = ptr;
	str.array = new_ezarray_dirty(CHAR, str.length);
	str.tostring = (char *)str.array.data;
	data = str.array.data;
	while (*src)
	{
		*((char*)str.array.data) = *(src);
		src++;
		str.array.data += str.array.data_size;
	}
	src = ptr;
	str.array.data = data;
	return (str);
}
