/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_size.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 01:11:29 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 20:23:58 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_SIZE_H
# define DATA_SIZE_H

unsigned char g_datasize[3][4] = (unsigned char[3][4]){
	{sizeof(char), sizeof(int), sizeof(float), sizeof(double)},
	{sizeof(char), sizeof(short int), sizeof(float), sizeof(double)},
	{sizeof(char), sizeof(long int), sizeof(float), sizeof(long double)}
};

#endif
