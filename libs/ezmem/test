/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 00:41:03 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/21 12:03:52 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ezmem.h>
#include <stdio.h>

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

void	print_int_ezarray(ARRAY ezarray)
{
	UINT	i = 0;
	int		*index;

	while (i < ezarray.length)
	{
		index = ezarray_get_index(ezarray, i);
		printf("\tindex %i of %i equals : %i\n", i, ezarray.length - 1, *index);
		i++;
	}
}

int main()
{
	ARRAY	ezarray;
	LINK	*ezlink;
	STRING	ezstring;
	int		*i;
	int		new_value;
	t_vec3	*vector;

	printf("Creating an ezarray of size 2000\n");
	ezarray = new_ezarray(signed_int, 2000);
	i = ezarray_get_index(ezarray, 0);
	printf("address 0 of 1999 : %p\n", i);
	*(&i[0]) = 10;
	*(&i[1]) = 20;
	*(&i[2]) = 30;
	*(&i[3]) = 40;
	*(&i[4]) = 50;
	i = ezarray_get_index(ezarray, 1);
	printf("address 1 of 1999 : %p\n", i);
	i = ezarray_get_index(ezarray, 2000);
	printf("address 2000 of 1999 : %p\n", i);
	i = ezarray_get_index(ezarray, 40000);
	printf("address 40000 of 1999 : %p\n", i);
	i = ezarray_get_index(ezarray, 0);
	printf("index 0 of 1999 equals : %i\n", *i);
	i = ezarray_get_index(ezarray, 1);
	printf("index 1 of 1999 equals : %i\nreallocating ezarray\n", *i);
	ezarray_realloc(&ezarray, 5);
	print_int_ezarray(ezarray);
	printf("pushing ezarray\n");
	new_value = 60;
	ezarray_push(&ezarray, &new_value);
	print_int_ezarray(ezarray);
	printf("shifting ezarray\n");
	ezarray_shift(&ezarray);
	print_int_ezarray(ezarray);
	printf("popping ezarray\n");
	ezarray_pop(&ezarray);
	print_int_ezarray(ezarray);
	printf("unshifting ezarray\n");
	new_value = 10;
	ezarray_unshift(&ezarray, &new_value);
	print_int_ezarray(ezarray);
	printf("%s\n", (ezstring = new_ezstring("This is a ezstring created using ezmem and returned using .tostring")).tostring);
	printf("Cleaning...\n");
	destroy_ezarray(&ezarray);
	destroy_ezstring(&ezstring);
	printf("Creating custom sized ezarray...\n");
	ezarray = new_ezarray_dirty(other, 2000, sizeof(t_vec3));
	vector = ezarray_get_index(ezarray, 0);
	*(vector) = (t_vec3){1, 2, 3};
	printf("index 0 of 1999 : %p\nvalues %f, %f, %f\n", vector, vector->x, vector->y, vector->z);
	vector = ezarray_get_index(ezarray, 1);
	printf("index 1 of 1999 : %p\n", vector);
	ezarray_push(&ezarray, &vector);
	vector = ezarray_get_index(ezarray, 2000);
	printf("index 2000 of 1999 : %p\n", vector);
	printf("Cleaning again...\n");
	destroy_ezarray(&ezarray);
	printf("Creating ezarray of type 'other' with no specified size (UNDEFINED BEHAVIOR, DON'T DO THIS !!!)...\n");
	ezarray = new_ezarray(other, 5);
	printf("ezarray data_size : %u\n", ezarray.data_size);
	i = ezarray_get_index(ezarray, 4);
	printf("index 4 of 4 : %p\n", i);
	printf("Cleaning again...\n");
	destroy_ezarray(&ezarray);
	printf("Creating new ezlink...\n");
	ezlink = new_ezlink(unsigned_int, 10);
	ezlink_append(ezlink, new_ezlink(unsigned_char, 100));
	printf("Next link adress %p\n", ezlink->next);
	destroy_ezlink(ezlink->next);
	printf("New next link adress %p\n", ezlink->next);
	ezlink_append(ezlink, new_ezlink(unsigned_char, 100));
	printf("New next link adress %p\n", ezlink->next);
	destroy_ezchain(ezlink);
	return (0);
}