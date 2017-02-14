/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shiftunshift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 23:19:56 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/26 00:45:41 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void	ezarray_shift(ARRAY *ezarray)
{
	char	*head;
	char	*tail;

	if (ezarray->length <= 1)
		return ;
	head = ezarray->data;
	tail = ezarray->data + ezarray->total_size;
	while ((char*)ezarray->data + ezarray->data_size != tail)
	{
		*((char*)ezarray->data) = *((char*)ezarray->data + ezarray->data_size);
		ezarray->data++;
	}
	ezarray->data = head;
	ezarray_realloc(ezarray, ezarray->length - 1);
}

void	ezarray_unshift(ARRAY *ezarray, void *element)
{
	char	*head;

	ezarray_realloc(ezarray, ezarray->length + 1);
	head = ezarray->data;
	ezarray->data = ezarray->data + ezarray->total_size;
	while ((char*)ezarray->data != head)
	{
		*((char*)ezarray->data) = *((char*)ezarray->data - ezarray->data_size);
		if (ezarray->data - ezarray->data_size == head)
			break ;
		ezarray->data--;
	}
	ezarray->data = head;
	if (element)
		while (ezarray->data != head + ezarray->data_size)
		{
			*((char*)ezarray->data) = *((char*)element);
			ezarray->data++;
			element++;
		}
	ezarray->data = head;
}
