/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:31:54 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/23 00:05:24 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sdl_framework.h>
#include <GL/gl.h>
#include <stdio.h>

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
	//put_image_pixel(get_attached_image(win), &color, mousepos);
	//put_window_pixel(win, &color, mousepos);
	put_window_image_pixel(win, &color, mousepos);
}

int main(int argc, char **argv)
{
	void	*framework;
	void	*winwin;
	void	*image;
	//t_rgba	color;
	//color = rgba(0, 125, 125, 100);
	framework = new_framework();
	winwin = new_window(framework, 768, 768, "test");
	set_window_clear_bits(winwin, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	printf("Current OpenGL version\n%s\n", glGetString(GL_VERSION));
	//image = new_image(framework, 4096, 4096);
	image = load_image_file(framework, "./Graphics_duck.bmp");
	//fill_image(image, &color);
	//color = rgba(255, 125, 125, 255);
	attach_image_to_window(winwin, image);
	refresh_window(winwin);
	assign_loop_hook(framework, new_callback(refresh, winwin));
	assign_keypress_hook(framework, winwin, SDL_SCANCODE_ESCAPE, new_callback(exit_framework, framework));
	assign_mousemove_hook(framework, winwin, new_callback(mousemove, winwin));
	//assign_keypress_hook(framework, winwin, SDL_SCANCODE_SPACE, new_callback(press, image));
	//assign_keyrepeat_hook(framework, winwin, SDL_SCANCODE_SPACE, new_callback(repeat, image));
	framework_loop(framework);
	return (argc + argv[0][0]);
}