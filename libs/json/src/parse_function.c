/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 12:22:53 by mbarbari          #+#    #+#             */
/*   Updated: 2016/03/31 12:16:04 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t		sub_pointer(char *json, char *json_backup)
{
	size_t	nb_move_pointer;

	nb_move_pointer = json - json_backup;
	return (nb_move_pointer);
}

void		skip_blanks(char **json)
{
	while (**json == ' ' || **json == '\n' || **json == '\t' || **json == '	')
		(*json)++;
}
