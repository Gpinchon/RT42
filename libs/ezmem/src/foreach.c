/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:38:53 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:33:51 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>

void	ezforeach(ARRAY array, void (*callback)(void *))
{
	UINT		ui;

	ui = 0;
	if (callback)
		while (ui < array.length)
		{
			callback(ezarray_get_index(array, ui));
			ui++;
		}
}
