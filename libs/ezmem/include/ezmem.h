/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezmem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 00:16:20 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:26:54 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EZMEM_H
# define EZMEM_H

# include <stdlib.h>
# include <string.h>

# define UCHAR 		unsigned char
# define UINT		unsigned int
# define TYPE		enum e_type
# define EZCALLBACK	void (*callback)(void *)
# define ARRAY		struct s_ezarray
# define LINK		struct s_ezlink
# define STRING		struct s_ezstring
# define BOOL		enum e_bool
# define SIGNED		0x000
# define UNSIGNED	0x100
# define SHORT		0x010
# define LONG		0x020
# define CHAR		0x000
# define INT		0x001
# define FLOAT		0x002
# define DOUBLE		0x003
# define OTHER		0x004

enum			e_type
{
	signed_char = SIGNED | CHAR,
	unsigned_char = UNSIGNED | CHAR,
	signed_short = SIGNED | SHORT | INT,
	unsigned_short = UNSIGNED | SHORT | INT,
	signed_long = SIGNED | LONG | INT,
	unsigned_long = UNSIGNED | LONG | INT,
	signed_int = SIGNED | INT,
	unsigned_int = UNSIGNED | INT,
	signed_float = FLOAT,
	signed_double = DOUBLE,
	long_double = LONG | DOUBLE,
	other = OTHER
};

enum			e_bool
{
	false = 0,
	true = !false
};

typedef struct	s_ezarray
{
	TYPE		type;
	UINT		data_size;
	UINT		length;
	UINT		total_size;
	void		*data;
}				t_ezarray;

typedef struct	s_ezlink
{
	ARRAY		array;
	LINK		*next;
	LINK		*prev;
}				t_ezlink;

typedef struct	s_ezstring
{
	UINT		length;
	char		*tostring;
	ARRAY		array;
}				t_ezstring;

ARRAY			new_ezarray(const TYPE datatype, UINT length, ...);
ARRAY			new_ezarray_dirty(const TYPE datatype, UINT length, ...);
STRING			new_ezstring(const char *src);
LINK			*new_ezlink(const TYPE datatype, UINT length, ...);
LINK			*new_ezlink_dirty(const TYPE datatype, UINT length, ...);
void			destroy_ezarray(ARRAY *ezarray);
void			destroy_ezstring(STRING *str);
void			destroy_ezlink(LINK *ezlink);
void			destroy_ezchain(LINK *from);
void			ezlink_append(LINK *chain, LINK *element);
void			*ezlink_get_data(LINK *link);
void			ezarray_push(ARRAY *ezarray, void *element);
void			ezarray_pop(ARRAY *ezarray);
void			ezarray_shift(ARRAY *ezarray);
void			ezarray_unshift(ARRAY *ezarray, void *element);
void			ezarray_realloc(ARRAY *ezarray, UINT new_length);
void			*ezarray_get_index(const ARRAY ezarray, const UINT index);
void			ezforeach(ARRAY array, void (*callback)(void *));
BOOL			ezarray_is_signed(const ARRAY ezarray);
void			*ezmemalloc(UINT size);

#endif
