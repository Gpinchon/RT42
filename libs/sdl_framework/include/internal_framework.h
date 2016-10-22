/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_framework.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:18:46 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/22 23:58:34 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_FRAMEWORK_H
# define INTERNAL_FRAMEWORK_H
# include <sdl_framework.h>
# include <stdlib.h>

# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK	0xff000000
#  define GMASK	0x00ff0000
#  define BMASK	0x0000ff00
#  define AMASK	0x000000ff
#  define CURENDIAN SDL_BIG_ENDIAN
# else
#  define RMASK	0x000000ff
#  define GMASK	0x0000ff00
#  define BMASK	0x00ff0000
#  define AMASK	0xff000000
#  define CURENDIAN SDL_LIL_ENDIAN
# endif

# define GSTRUCT	struct s_generic
# define MAX_REPEAT	2
# define MAX_WIN	50
# define MAX_SCAN	300
# define MAX_BUTTON	5

typedef struct	s_generic
{
	GSTRUCT		*next;
	GSTRUCT		*prev;
	void		*data;
	size_t		size;
}				t_generic;

typedef struct	s_img
{
	SDL_Surface	*sdl_surface;
}				t_img;

typedef struct	s_window
{
	t_rgb		clear_color;
	Uint32		id;
	SDL_Surface	*sdl_surface;
	SDL_Window	*sdl_window;
	SDL_GLContext	*gl_context;
	GLbitfield  clear_bits;
	GSTRUCT		*attached_image;
}				t_window;

typedef struct	s_framework
{
	GSTRUCT		*windows;
	GSTRUCT		*images;
	SDL_bool	done;
	t_callback	loop;
	t_callback	keydown[MAX_WIN][MAX_SCAN][MAX_REPEAT];
	t_callback	keyup[MAX_WIN][MAX_SCAN];
	t_callback	mousedown[MAX_WIN][MAX_BUTTON];
	t_callback	mouseup[MAX_WIN][MAX_BUTTON];
	t_callback	mousemove[MAX_WIN];
	Uint8		keys[MAX_SCAN];
	Uint8		buttons[MAX_BUTTON];
	t_point2	mousepos;
	t_point2	lastmousepos;
}				t_framework;

void	*add_image(t_framework *framework, GSTRUCT *img);
void	*get_image_pixel(void *image, t_point2 position);
void	*get_window_pixel(void *window, t_point2 position);
void	destroy_framework(void *framework);
void	*int_memset(void *str, int c, size_t n);
void	*int_memalloc(size_t size);
void	*new_object(size_t size);
void	*append_object(t_generic *new_object, t_generic *from_object);
void	*get_data_pointer(t_generic *object, size_t size);
void	destroy_objects(t_generic *from_object);
void	init_errors(void);
void	int_putstr_fd(char const *s, int fd);
void	int_putendl_fd(char const *s, int fd);
void	int_putnbr_fd(int n, int fd);
Uint32	map_color(SDL_Surface *surface, void *color);

#endif
