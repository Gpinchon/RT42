/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_framework.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:11:11 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/24 18:54:08 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

static void	init_keys(t_framework *f)
{
	int	i, j;

	i = 0;
	while (i < MAX_WIN)
	{
		f->mousemove[i].function = NULL;
		f->mousemove[i].arg = NULL;
		j = 0;
		while (j < MAX_SCAN)
		{
			f->keydown[i][j][0].function = NULL;
			f->keydown[i][j][1].function = NULL;
			f->keydown[i][j][0].arg = NULL;
			f->keydown[i][j][1].arg = NULL;
			f->keyup[i][j].function = NULL;
			f->keyup[i][j].arg = NULL;
			f->keys[j] = 0;
			j++;
		}
		i++;
	}
}

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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	init_keys(framework);
	return (framework);
}
