/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 16:43:39 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/24 19:36:53 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*add_image(t_framework *framework, GSTRUCT *img)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "add_image");
	FRAMEWORK_DEBUG(!img, NULL_IMAGE_POINTER, "add_image");
	if (!framework->images)
		return (framework->images = img);
	else
		return (append_object((void*)img, (void*)framework->images));
}

void	*new_image(void *framework, int width, int heigth)
{
	GSTRUCT	*gstruct;

	gstruct = new_object(sizeof(t_img));
	((t_img*)gstruct->data)->sdl_surface = SDL_CreateRGBSurface(0, width, heigth,
		32, RMASK, GMASK, BMASK, AMASK);
	return (add_image(framework, gstruct));
}

IMGDATA	get_image_data(void *image)
{
	t_img	*img;
	IMGDATA	data;

	img = get_data_pointer(image, sizeof(t_img));
	data.size = (t_point2){img->sdl_surface->w, img->sdl_surface->h};
	data.pixels = img->sdl_surface->pixels;
	data.bpp = img->sdl_surface->format->BitsPerPixel;
	data.sizeline = img->sdl_surface->format->BytesPerPixel;
	data.endian = CURENDIAN;
	return (data);
}

void	get_image_size(void *image, int *width, int *heigth)
{
	t_img	*img;

	img = get_data_pointer(image, sizeof(t_img));
	*width = img->sdl_surface->w;
	*heigth = img->sdl_surface->h;
}
