/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:06:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/13 17:12:29 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <sdl_framework/include/sdl_framework.h>
# include <vml/include/vml.h>
# include <ezmem/include/ezmem.h>
# define ENGINE	struct s_engine

typedef struct	s_framebuffer
{
	void		*pixel;
	ARRAY		array;
	t_point2	size;
	t_rgba		color;
}				t_framebuffer;

typedef struct	s_engine
{
	void		*framwork;
	void		*window;
	void		*framebuffer;
}				t_engine;

#endif