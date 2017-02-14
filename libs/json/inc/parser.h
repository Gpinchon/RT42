/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 11:28:23 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/07 14:51:55 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "parser_union.h"

# define TYPE_ERROR		-1
# define TYPE_OBJECT	0
# define TYPE_ARRAY		1
# define TYPE_BOOL		2
# define TYPE_NUMBER	3
# define TYPE_STRING	4

struct t_json;
struct t_json_arr;

typedef struct	s_value {
	int				type;
	union u_data	data;
	int				error;
}				t_value;

typedef struct	s_json {
	char			*key;
	t_value			value;
	struct s_json	*next;
}				t_json;

typedef struct	s_json_arr {
	t_value				value;
	struct s_json_arr	*next;
}				t_json_arr;

t_json_arr		*parse_arr(char **json);
t_json			*parse_obj(char **json);
t_json			*parse_obj2(char **json, t_json *value);
t_value			parser(char *file_name);
size_t			sub_pointer(char *json, char *json_backup);
void			skip_blanks(char **json);
int				if_number(char c);
char			*parse_string(char **json);
double			parse_number(char **json);
int				parse_boolean(char **json);
void			def_value(char **json, t_value *value);
void			parser_value(char **json, t_value *value);
t_value			json_get(t_json *x, char *str);
void			json_foreach_obj(t_json *x,
	void (cb)(t_value, char *s, void*), void *a);
void			json_foreach_arr(t_json_arr *x,
	void (cb)(t_value, int, void*), void *a);
int				json_arr_length(t_json_arr *x);
void			json_free(t_value value);

#endif
