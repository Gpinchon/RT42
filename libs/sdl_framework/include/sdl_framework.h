/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_framework.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 14:15:47 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 13:00:02 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_FRAMEWORK_H
# define SDL_FRAMEWORK_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include <unistd.h>

# define RGBCOL					0x24
# define RGBACOL				0x32
# define IMGDATA				t_img_data
# ifndef STDERR_FILENO
#  define STDERR_FILENO 1
# endif

/*
** Error codes
*/
# define MAX_ERROR				0xFF
# define ALL_OK					0x0
# define NULL_WINDOW_POINTER	0x1
# define NULL_IMAGE_POINTER		0x2
# define NULL_FRAMEWORK_POINTER	0x3
# define SDL_ERROR				0x4
# define MALLOC_ERROR			0x5
# define WRONG_IMAGE_COORD		0x6
# define NO_WINDOWS				0x7
# define NULL_OBJECT_POINTER	0x8
# define INVALID_KEYCODE		0x9
# define INVALID_WINDOW_SIZE	0xA
# define INVALID_DATA_SIZE		0xB
# define NULL_DATA_POINTER		0xC
# define NULL_COLOR_POINTER		0xD
# define NULL_SURFACE_POINTER	0xE
# define UNKNOW_COLOR_TYPE		0xF

char	*g_errors[MAX_ERROR];

/*
** Comment/uncomment to debug framework
*/
/*
** # define DEBUG
*/

/*
** Comment/uncomment to exit on error
*/
# define EXIT_ON_ERROR

# ifdef DEBUG
#  ifdef EXIT_ON_ERROR
#   define RETURN exit(-42)
#  else
#   define RETURN
#  endif
#  define FRAMEWORK_DEBUG(cond, c, fn)	if(cond){print_error(c, fn);RETURN;}
# else
#  define FRAMEWORK_DEBUG(cond, c, fn)
# endif

# define CLEAR_COLOR	rgb(0, 0, 0)

typedef struct	s_point2
{
	int			x;
	int			y;
}				t_point2;

typedef struct	s_rgb
{
	Uint8		type;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_rgb;

typedef struct	s_rgba
{
	Uint8		type;
	Uint8		r;
	Uint8		g;
	Uint8		b;
	Uint8		a;
}				t_rgba;

typedef struct	s_img_data
{
	t_point2	size;
	Uint8		bpp;
	Uint8		opp;
	Uint16		endian;
	Uint32		sizeline;
	void		*pixels;
}				t_img_data;

typedef struct	s_callback
{
	void		(*function)();
	void		*arg;
}				t_callback;

/*
** Custom variable creations
*/
void			*new_framework(void);
void			*new_window(void *framework, int width, int height, char *name);
void			*new_image(void *framework, int width, int heigth);
void			*new_gl_context(void *window);
t_callback		new_callback(void (*fun)(), void *arg);
Uint32			get_ticks();
/*
** Custom variables destruction
*/
void			destroy_framework(void *framework);
void			exit_framework(void *framework);
void			destroy_window(void *framework, void *window);
void			destroy_windows(void *framework);
void			destroy_image(void *framework, void *image);
void			destroy_images(void *framework);
/*
** Color management functions
** Call map_color with a pointer
*/
t_rgb			rgb(Uint8 r, Uint8 g, Uint8 b);
t_rgba			rgba(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
/*
** Window filling/clearing functions
** void *color is the adress of a t_rgb/t_rgba structure
*/
void			*clear_window(void *window);
void			*clear_window_image(void *window);
void			set_window_clear_bits(void *window, GLbitfield clear_bits);
void			*refresh_window(void *window);
void			*fill_window(void *window, void *color);
/*
** Image filling/clearing/management functions
** void *color is the adress of a t_rgb/t_rgba structure
*/
void			*load_image_file(void *framework, const char *path);
void			*fill_image(void *image, void *color);
void			*get_attached_image(void *window);
void			*attach_image_to_window(void *window, void *image);
void			*put_image(void *window, void *image, t_point2 position);
void			*put_image_stretched(void *window, void *image);
void			get_image_size(void *image, int *width, int *heigth);
IMGDATA			get_image_data(void *image);
/*
** Pixel put functions, use to put a color
** (pointer to an rgb(a) struct) to image/window
*/
t_rgba			get_image_pixel_rgba(void *image, t_point2 coord);
void			*get_image_pixel(void *image, t_point2 position);
void			*get_window_pixel(void *window, t_point2 position);
void			*put_image_pixel(void *image, void *color, t_point2 position);
void			*put_window_pixel(void *window, void *color, t_point2 position);
void			*put_window_image_pixel(void *window, void *color,
											t_point2 position);
/*
** Print error to standard error file descriptor
*/
void			print_error(int error_code, const char *function_name);
/*
** Loop functions
** framework_loop returns when exit_framework is called
*/
Uint8			get_key_status(void *framework, Uint32 keycode);
Uint8			get_button_status(void *framework, Uint8 button);
Uint8			mousemoved(void	*framework);
t_point2		get_mouse_pos(void *framework);
t_point2		get_last_mouse_pos(void *framework);
void			framework_loop(void *framework);
void			framework_loop_once(void *framework);
char			framework_is_done(void *framework);
/*
** loop_hook prototype == void callback(void *arg);
*/
void			set_loop_hook(void *framework, t_callback callback);
void			set_onexit_hook(void *framework, t_callback callback);
/*
** keyup/down/press_hook prototype == void callback(void *arg, Uint32 keycode);
*/
void			set_keyup_hook(void *framework, void *window,
	char *keyname, t_callback callback);
void			set_keypress_hook(void *framework, void *window,
	char *keyname, t_callback callback);
void			set_keyrepeat_hook(void *framework, void *window,
	char *keyname, t_callback callback);
/*
** mousemove_hook prototype ==void callback(void *arg, t_point2 mouse_position);
*/
void			set_mousemove_hook(void *framework, void *window,
	t_callback callback);
/*
** mousedown/up_hook prototype == void callback(void *arg, Uint8 button);
*/
void			set_mousedown_hook(void *framework, void *window,
	Uint8 button, t_callback callback);
void			set_mouseup_hook(void *framework, void *window,
	Uint8 button, t_callback callback);

#endif
