/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:57:58 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/18 18:56:42 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void	blit_framebuffer_scaled(FRAMEBUFFER buf, void *image)
{
	t_rgba		rgbacol;
	UCHAR		*bufpixel;
	VEC2		coord;
	VEC2		icoord;
	t_point2	imgsize;

	imgsize = get_image_data(image).size;
	coord = new_vec2(0, 0);
	icoord = new_vec2(0, 0);
	while (icoord.y < imgsize.y)
	{
		coord.x = 0;
		icoord.x = 0;
		while (icoord.x < imgsize.x)
		{
			bufpixel = get_buffer_value(buf, (t_point2){coord.x, coord.y});
			rgbacol = rgba(bufpixel[2], bufpixel[1], bufpixel[0], bufpixel[3]);
			put_image_pixel(image, &rgbacol, (t_point2){icoord.x, icoord.y});
			coord.x += (float)buf.size.x / (float)imgsize.x;
			icoord.x++;
		}
		coord.y += (float)buf.size.y / (float)imgsize.y;
		icoord.y++;
	}
}

void		display_framebuffer(FRAMEBUFFER buf, void *image)
{
	UINT	j;
	IMGDATA	i;

	j = 0;
	i = get_image_data(image);
	if (i.size.x == buf.size.x
	&& i.size.y == buf.size.y
	&& i.bpp == buf.bpp)
		while (j < buf.array.length)
		{
			((UCHAR*)i.pixels)[j] = *((UCHAR*)ezarray_get_index(buf.array, j));
			j++;
		}
	else if (i.bpp == buf.bpp)
		blit_framebuffer_scaled(buf, image);
}

void		copy_framebuffer(FRAMEBUFFER f1, FRAMEBUFFER f2)
{
	t_point2	coord[2];
	UCHAR		*color;

	coord[0].x = 0;
	coord[1] = f1.size;
	while (coord[0].x < coord[1].x)
	{
		coord[0].y = 0;
		while (coord[0].y < coord[1].y)
		{
			color = get_buffer_value(f1, coord[0]);
			put_pixel_to_buffer(f2, coord[0], new_vec4(color[2] / 255.f,
				color[1] / 255.f, color[0] / 255.f, color[3] / 255.f));
			coord[0].y++;
		}
		coord[0].x++;
	}
}
