/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_set_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:54:30 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/20 15:24:51 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	set_loop_hook(void *framework, t_callback callback)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_loop_hook");
	((t_framework*)framework)->loop = callback;
}

void	set_lowmem_hook(void *framework, t_callback callback)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_lowmem_hook");
	((t_framework*)framework)->low_mem = callback;
}

void	set_onexit_hook(void *framework, t_callback callback)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_onexit_hook");
	((t_framework*)framework)->onexit = callback;
}
