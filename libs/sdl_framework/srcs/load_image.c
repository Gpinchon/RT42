/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 22:18:47 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 17:03:55 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>
#include <stdio.h>

void			convert_bmp(SDL_Surface *bmp_img)
{
	Uint8	*pixel_temp = int_memalloc((sizeof(Uint8) * bmp_img->h * bmp_img->w) * 4);
	Uint8	a, b, g, r;
	int		i = 0, j = 0, x, y;

	SDL_LockSurface(bmp_img);
	for (y = 0; y < bmp_img->h; y++)
	{
		for(x = 0; x < bmp_img->w; x++)
		{
			a = ((Uint8*)bmp_img->pixels)[i];
			b = ((Uint8*)bmp_img->pixels)[i+1];
			g = ((Uint8*)bmp_img->pixels)[i+2];
			r = ((Uint8*)bmp_img->pixels)[i+3];
			pixel_temp[j] = a;
			pixel_temp[j+1] = r;
			pixel_temp[j+2] = g;
			pixel_temp[j+3] = b;
			i+=4;
			j+=4;
		}
	}
	free(bmp_img->pixels);
	bmp_img->pixels = pixel_temp;
	SDL_FreeFormat(bmp_img->format);
	bmp_img->format = SDL_AllocFormat(SDL_PIXELFORMAT_BGRA8888);
	SDL_UnlockSurface(bmp_img);
}

void	*load_image_file(void *framework, const char *path)
{
	GSTRUCT			*istruct;
	SDL_Surface		*bmp;

	istruct = new_object(sizeof(t_img));
	bmp = SDL_LoadBMP(path);
	FRAMEWORK_DEBUG(!bmp, SDL_ERROR, "load_image_file");
	SDL_LockSurface(bmp);
	if (bmp->format->BitsPerPixel == 32)
	{
		SDL_FreeFormat(bmp->format);
		bmp->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	}
	((t_img*)istruct->data)->sdl_surface = bmp;
	SDL_UnlockSurface(bmp);
	return (add_image(framework, istruct));
}
