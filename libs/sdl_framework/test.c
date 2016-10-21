/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:31:54 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 17:30:00 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sdl_framework.h>
//#include <GL/gl.h>
#include <stdio.h>

#define UCHAR 	unsigned char
#define UINT	unsigned int
#define TYPE		e_type
#define ARRAY		t_array
#define STRING		t_string
#define BOOL		e_bool
#define SIGNED		0x000
#define UNSIGNED	0x100
#define SHORT		0x010
#define LONG		0x020
#define CHAR		0x000
#define INT			0x001
#define FLOAT		0x002
#define DOUBLE		0x003
#define OTHER		0x004
//#define ENUM		0x006

typedef enum {
	signed_char = SIGNED | CHAR,
	unsigned_char = UNSIGNED | CHAR,
	signed_short = SIGNED | SHORT | INT,
	unsigned_short = UNSIGNED | SHORT | INT,
	signed_long = SIGNED | LONG | INT,
	unsigned_long = UNSIGNED | LONG | INT,
	signed_int = SIGNED | INT,
	unsigned_int = UNSIGNED | INT,
	signed_float = FLOAT,
	signed_double = DOUBLE,
	long_double = LONG | DOUBLE,
	other = OTHER
} e_type;

UCHAR g_datasize[3][4] = (UCHAR[3][4]){
	{sizeof(char), sizeof(int), sizeof(float), sizeof(double)},
	{sizeof(char), sizeof(short int), sizeof(float), sizeof(double)},
	{sizeof(char), sizeof(long int), sizeof(float), sizeof(long double)}
};

typedef enum {
	false = 0,
	true = !false
} e_bool;

typedef struct	s_array
{
	UCHAR		data_size;
	TYPE		type;
	UINT		length;
	UINT		total_size;
	void		*data;
}				t_array;

typedef struct	s_string
{
	UINT		length;
	char		*tostring;
	t_array		array;
}				t_string;

void		*get_array_index(const ARRAY array, const UINT index)
{
	return (index < array.length
		&& array.data ? array.data + index * array.data_size : NULL);
}

BOOL		array_is_signed(const ARRAY array)
{
	return (!(array.type & 0x100));
}

/*	
printf("datatype : %i\n", (datatype & 0x00F));
printf("Signed ? %s\n", datatype & 0x100 ? "No" : "Yes");
printf("Data size %i\n", array.data_size);
*/

void		destroy_array(ARRAY *array)
{
	if (array->total_size)
		free(array->data);
	*array = (ARRAY){0, 0x000, 0, 0, NULL};
}

void		destroy_string(STRING *str)
{
	destroy_array(&str->array);
	str->length = 0;
	str->tostring = NULL;
}

t_array		new_array(const TYPE datatype, UINT length, ...)
{
	t_array	array;
	va_list	argptr;

	array.type = datatype;
	array.length = length;
	if ((datatype & 0x00F) < 4)
		array.data_size = g_datasize[(datatype & 0x0F0) >> 4][datatype & 0x00F];
	else
	{
		va_start(argptr, 0);
		array.data_size = va_arg(argptr, int);
	}	
	array.data = malloc(array.length * array.data_size + 1);
	array.total_size = array.length * array.data_size + 1;
	while (length)
	{
		((char*)array.data)[length * array.data_size] = 0;
		length--;
	}
	return (array);
}

t_array		new_array_dirty(const TYPE datatype, UINT length, ...)
{
	t_array	array;
	va_list	argptr;

	array.type = datatype;
	array.length = length;
	if ((datatype & 0x00F) < 4)
		array.data_size = g_datasize[(datatype & 0x0F0) >> 4][datatype & 0x00F];
	else
	{
		va_start(argptr, 0);
		array.data_size = va_arg(argptr, int);
	}	
	array.data = malloc(array.length * array.data_size + 1);
	array.total_size = array.length * array.data_size + 1;
	((char*)array.data)[array.total_size - 1] = 0;
	return (array);
}

t_string	new_string(const char *src)
{
	t_string str;
	const char	*ptr;
	void		*data;

	ptr = src;
	str.length = 0;
	while (*src)
	{
		str.length++;
		src++;
	}
	src = ptr;
	str.array = new_array_dirty(CHAR, str.length);
	str.tostring = (char *)str.array.data;
	data = str.array.data;
	while (*src)
	{
		*((char*)str.array.data) = *(src);
		src++;
		str.array.data += str.array.data_size;
	}
	src = ptr;
	str.array.data = data;
	return (str);
}

void	press(void *image)
{
	t_rgba	color;
	int w, h;

	color = rgba(255, 255, 0, 255);
	get_image_size(image, &w, &h);
	put_image_pixel(image, &color, (t_point2){rand() / (float)RAND_MAX * w, rand() / (float)RAND_MAX * h});
}

void	repeat(void *image)
{
	t_rgba	color;
	int w, h, i = 0;

	get_image_size(image, &w, &h);
	while (i < w)
	{
		color = rgba(rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255);
		put_image_pixel(image, &color, (t_point2){rand() / (float)RAND_MAX * i, rand() / (float)RAND_MAX * h});
		i++;
	}
}

void	refresh(void *window)
{
	//t_rgba	color;
	//int w, h, i = 0;

	//clear_window(window);
	//get_image_size(get_attached_image(window), &w, &h);
	//refresh_window(window);
	//while (i < w)
	//{
	//	color = rgba(rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255);
	//	put_image(window, get_attached_image(window), (t_point2){rand() / (float)RAND_MAX * 512, rand() / (float)RAND_MAX * 512});
	//	put_image_pixel(get_attached_image(window), &color, (t_point2){rand() / (float)RAND_MAX * i, rand() / (float)RAND_MAX * h});
	//	put_window_pixel(window, &color, (t_point2){rand() / (float)RAND_MAX * 768, rand() / (float)RAND_MAX * 768});
	//	i++;
	//}
	//clear_window_image(window);
	//put_image(window, get_attached_image(window), (t_point2){rand() / (float)RAND_MAX * 1024, rand() / (float)RAND_MAX * 1024});
	//repeat(get_attached_image(window));
	refresh_window(window);
}

void	mousemove(void *win, t_point2 mousepos)
{
	t_rgba	color;

	color = rgba(rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255);
	put_window_pixel(win, &color, mousepos);
}

int main(int argc, char **argv)
{
	//new_array(UNSIGNED | DOUBLE, 4);
	STRING str = new_string("Coucou !");
	printf("New string : %s\n", str.tostring);
	destroy_string(&str);
	void	*framework;
	void	*winwin;
	//void	*image;
	//t_rgba	color;
	//color = rgba(0, 125, 125, 100);
	framework = new_framework();
	winwin = new_window(framework, 768, 768, "test");
	set_window_clear_bits(winwin, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	printf("Current OpenGL version\n%s\n", glGetString(GL_VERSION));
	//image = new_image(framework, 4096, 4096);
	//image = load_image_file(framework, "./Graphics_duck.bmp");
	//fill_image(image, &color);
	//color = rgba(255, 125, 125, 255);
	//attach_image_to_window(winwin, image);
	refresh_window(winwin);
	assign_loop_hook(framework, new_callback(refresh, winwin));
	assign_keypress_hook(framework, winwin, SDL_SCANCODE_ESCAPE, new_callback(exit_framework, framework));
	assign_mousemove_hook(framework, winwin, new_callback(mousemove, winwin));
	//assign_keypress_hook(framework, winwin, SDL_SCANCODE_SPACE, new_callback(press, image));
	//assign_keyrepeat_hook(framework, winwin, SDL_SCANCODE_SPACE, new_callback(repeat, image));
	framework_loop(framework);
	return (argc + argv[0][0]);
}