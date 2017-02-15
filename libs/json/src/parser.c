/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 12:50:55 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/15 16:48:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stream.h"
#include "libft.h"

t_json		*parse_obj2(char **json, t_json *value)
{
	value->next = NULL;
	if (**json == ',')
	{
		*json += 1;
		value->next = parse_obj(json);
		return (value);
	}
	else if (**json == '}')
	{
		*json += 1;
		return (value);
	}
	else
		return (NULL);
}

t_json		*parse_obj(char **json)
{
	t_json	*value;
	size_t	size;

	skip_blanks(json);
	if (**json != '"')
		return (NULL);
	*json += 1;
	size = sub_pointer(ft_strchr(*json + 1, '"'), *json);
	if (size >= 5242880)
		return (NULL);
	value = (t_json*)ft_memalloc(sizeof(t_json));
	value->key = ft_strsub(*json, 0, size);
	*json = *json + ft_strlen(value->key) + 1;
	skip_blanks(json);
	if (**json != ':')
		return (NULL);
	*json += 1;
	skip_blanks(json);
	parser_value(json, &value->value);
	skip_blanks(json);
	if (parse_obj2(json, value) == NULL)
		return (NULL);
	else
		return (value);
}

t_json_arr	*parse_arr(char **json)
{
	t_json_arr	*value;

	skip_blanks(json);
	if (**json == ']')
		return (NULL);
	value = (t_json_arr*)ft_memalloc(sizeof(t_json_arr));
	parser_value(json, &value->value);
	skip_blanks(json);
	if (**json == ',')
	{
		*json += 1;
		value->next = parse_arr(json);
	}
	else if (**json == ']')
		return (value);
	return (value);
}

t_value		parser(char *file_name)
{
	int			fd;
	char		*line;
	char		*linetofree;
	t_stream	stream;
	t_value		value;

	line = NULL;
	value = (t_value){.type = 0, .error = 0};
	fd = open(file_name, O_RDONLY);
	create_stream(fd, &stream);
	while (!value.error && read_until(&stream, &line, '\0') > 0)
	{
		linetofree = line;
		if (*line == '{')
		{
			value.type = 0;
			line += 1;
			value.data.obj = parse_obj(&line);
		}
		else
			value.error = TYPE_ERROR;
		free(linetofree);
		line = NULL;
	}
	return (value);
}
