/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 11:23:33 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/10 09:17:47 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_value		json_get(t_json *parse, char *str)
{
	t_json	*x;
	t_value	value;
	char	*split;

	x = parse;
	while (x != NULL)
	{
		split = ft_strchr(str, '.');
		if (split == NULL && ft_strcmp(str, x->key) == 0)
			return (x->value);
		x = x->next;
	}
	value.error = TYPE_ERROR;
	return (value);
}

void		json_foreach_obj(t_json *parse, void (cb)(t_value, char *s, void*),
		void *a)
{
	t_json	*x;

	x = parse;
	while (x != NULL)
	{
		(cb)(x->value, x->key, a);
		x = x->next;
	}
}

void		json_foreach_arr(t_json_arr *parse, void (cb)(t_value, int, void*),
		void *a)
{
	int			i;
	t_json_arr	*x;

	x = parse;
	i = 0;
	while (x != NULL)
	{
		(cb)(x->value, i, a);
		x = x->next;
		i++;
	}
}

int			json_arr_length(t_json_arr *parse)
{
	int			i;
	t_json_arr	*x;

	x = parse;
	i = 0;
	while (x != NULL)
	{
		x = x->next;
		i++;
	}
	return (i);
}
