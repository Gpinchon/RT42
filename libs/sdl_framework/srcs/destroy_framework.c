/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_framework.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:36:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 21:33:16 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	destroy_framework(void *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "destroy_framework");
	if (((t_framework *)framework)->windows)
		destroy_windows(((t_framework *)framework)->windows);
	if (((t_framework *)framework)->images)
		destroy_images(((t_framework *)framework)->images);
	free(framework);
	SDL_Quit();
}

void	exit_framework(void *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "destroy_framework");
	((t_framework *)framework)->done = SDL_TRUE;
}
