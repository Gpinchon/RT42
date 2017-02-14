/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 14:22:34 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/10 09:15:29 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stream.h"
#include "libft.h"

void		json_free_array(t_value value)
{
	t_json_arr	*obj;
	void		*next;

	obj = value.data.arr;
	while (obj)
	{
		json_free(obj->value);
		next = obj->next;
		free(obj);
		obj = next;
	}
}

void		json_free(t_value value)
{
	t_json		*obj;
	void		*next;

	obj = value.data.obj;
	while (obj)
	{
		if (obj->value.type == TYPE_OBJECT)
			json_free(obj->value);
		if (obj->value.type == TYPE_ARRAY)
			json_free_array(obj->value);
		next = obj->next;
		if (obj->value.type == TYPE_STRING)
			free(obj->value.data.s);
		if (obj->key)
			free(obj->key);
		free(obj);
		obj = next;
	}
}
