/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_framework.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:11:11 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/06 19:02:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*new_framework(void)
{
	t_framework	*framework;

	init_errors();
	framework = int_memalloc(sizeof(t_framework));
	FRAMEWORK_DEBUG(!framework, MALLOC_ERROR, "new_framework");
	FRAMEWORK_DEBUG(SDL_Init(SDL_INIT_EVERYTHING), SDL_ERROR, "new_framework");
	SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return (framework);
}
