/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:31:43 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:34:20 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>
#include <stdarg.h>

LINK		*new_ezlink(const TYPE datatype, UINT length, ...)
{
	LINK	*ezlink;
	va_list	argptr;

	ezlink = ezmemalloc(sizeof(LINK));
	if ((datatype & 0x00F) >= 4)
	{
		va_start(argptr, length);
		ezlink->array = new_ezarray(datatype, length, va_arg(argptr, UINT));
	}
	else
		ezlink->array = new_ezarray(datatype, length);
	return (ezlink);
}

LINK		*new_ezlink_dirty(const TYPE datatype, UINT length, ...)
{
	LINK	*ezlink;
	va_list	argptr;

	ezlink = ezmemalloc(sizeof(LINK));
	if ((datatype & 0x00F) >= 4)
	{
		va_start(argptr, length);
		ezlink->array = new_ezarray_dirty(datatype, length,
				va_arg(argptr, UINT));
	}
	else
		ezlink->array = new_ezarray_dirty(datatype, length);
	return (ezlink);
}
