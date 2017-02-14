/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:45:27 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/06 21:54:47 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	destroy_image(void *framework, void *image)
{
	GSTRUCT		*gstruct;
	t_img		*img;
	SDL_Surface	*surface;

	gstruct = NULL;
	FRAMEWORK_DEBUG(!image, NULL_WINDOW_POINTER, "destroy_image");
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "destroy_image");
	if (image == ((t_framework*)framework)->images)
		((t_framework*)framework)->images = ((GSTRUCT*)image)->next;
	if ((gstruct = ((GSTRUCT*)image)->prev))
	{
		gstruct->next = ((GSTRUCT*)image)->next;
		if (gstruct->next)
			gstruct->next->prev = gstruct;
	}
	else if ((gstruct = ((GSTRUCT*)image)->next))
		gstruct->prev = NULL;
	img = get_data_pointer(image, sizeof(t_img));
	surface = img->sdl_surface;
	free(img);
	free(image);
	SDL_FreeSurface(surface);
}

void	destroy_images(void *f)
{
	GSTRUCT	*img[2];

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "destroy_images");
	img[0] = ((t_framework*)f)->images;
	while (img[0])
	{
		img[1] = img[0]->next;
		destroy_image(f, img[0]);
		img[0] = img[1];
	}
}
