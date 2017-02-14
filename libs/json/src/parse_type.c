/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 12:18:49 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/08 16:45:40 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char		*parse_string(char **json)
{
	char *s;

	s = ft_strsub(*json, 0, sub_pointer(ft_strchr(*json, '"'), *json));
	*json += ft_strlen(s) + 1;
	return (s);
}

double		parse_number(char **json)
{
	return (strtof(*json, json));
}

int			parse_boolean(char **json)
{
	int boolean;

	boolean = ft_strncmp(*json, "true", 4) == 0 ? 1 : 0;
	if (boolean == 1)
		*json += 4;
	else
		*json += 5;
	return (boolean);
}

void		def_value(char **json, t_value *value)
{
	if (**json == '"')
		value->type = TYPE_STRING;
	else if (**json == '{')
		value->type = TYPE_OBJECT;
	else if (**json == '[')
		value->type = TYPE_ARRAY;
	else if (ft_strncmp(*json, "true", 4) == 0 || ft_strncmp(*json, "false", 5)
		== 0)
		value->type = TYPE_BOOL;
	else if (ft_isdigit(**json) || (**json == '-') || (**json == '+'))
		value->type = TYPE_NUMBER;
}

void		parser_value(char **json, t_value *value)
{
	def_value(json, value);
	if (**json == '"')
	{
		*json += 1;
		value->data.s = parse_string(json);
	}
	else if (**json == '{')
	{
		*json += 1;
		value->data.obj = parse_obj(json);
	}
	else if (**json == '[')
	{
		*json += 1;
		value->data.arr = parse_arr(json);
		*json += sub_pointer(ft_strchr(*json, ']'), *json) + 1;
	}
	else if (ft_strncmp(*json, "true", 4) == 0 || ft_strncmp(*json, "false", 5)
		== 0)
		value->data.boolean = parse_boolean(json);
	else if (ft_isdigit(**json) || (**json == '-') || (**json == '+'))
		value->data.number = parse_number(json);
}
