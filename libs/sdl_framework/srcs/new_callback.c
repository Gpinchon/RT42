/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_callback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 20:48:39 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 20:50:46 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

t_callback	new_callback(void (*fun)(), void *arg)
{
	return ((t_callback){fun, arg});
}
