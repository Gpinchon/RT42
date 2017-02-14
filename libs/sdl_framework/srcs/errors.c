/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 13:02:30 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/22 22:17:28 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_framework.h>
#include <internal_framework.h>

void	init_errors(void)
{
	int i;

	i = -1;
	while (i < MAX_ERROR)
		g_errors[i++] = "Undefined error";
	g_errors[ALL_OK] = "All is ok";
	g_errors[NULL_WINDOW_POINTER] = "Null window pointer";
	g_errors[NULL_IMAGE_POINTER] = "Null image pointer";
	g_errors[NULL_FRAMEWORK_POINTER] = "Null framework pointer";
	g_errors[SDL_ERROR] = "SDL Error";
	g_errors[MALLOC_ERROR] = "Malloc Error";
	g_errors[WRONG_IMAGE_COORD] = "Wrong image coordinates";
	g_errors[NO_WINDOWS] = "No windows found";
	g_errors[INVALID_KEYCODE] = "Invalid keycode";
	g_errors[INVALID_WINDOW_SIZE] = "Invalid window size";
	g_errors[NULL_OBJECT_POINTER] = "Null object pointer";
	g_errors[INVALID_DATA_SIZE] = "Invalid data size";
	g_errors[NULL_DATA_POINTER] = "Null data pointer";
	g_errors[NULL_COLOR_POINTER] = "Null color pointer";
	g_errors[NULL_SURFACE_POINTER] = "Null surface pointer";
	g_errors[UNKNOW_COLOR_TYPE] = "Unknown color type";
}

void	print_error(int error_code, const char *function_name)
{
	if (error_code >= 0 && error_code < MAX_ERROR)
		int_putstr_fd(g_errors[error_code], STDERR_FILENO);
	else
	{
		int_putstr_fd("Incorrect error code : ", STDERR_FILENO);
		int_putnbr_fd(error_code, STDERR_FILENO);
	}
	int_putstr_fd(" in ", STDERR_FILENO);
	int_putendl_fd((char*)function_name, STDERR_FILENO);
	if (error_code == SDL_ERROR)
		int_putendl_fd(SDL_GetError(), STDERR_FILENO);
}
