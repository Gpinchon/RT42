/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:56:10 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:46:20 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	destroy_objects(t_generic *from_object)
{
	t_generic	*obj[2];

	obj[0] = from_object;
	FRAMEWORK_DEBUG(!from_object, NULL_OBJECT_POINTER, "destroy_objects");
	while (obj[0])
	{
		obj[1] = obj[0]->next;
		free(obj[0]->data);
		free(obj[0]);
		obj[0] = obj[1];
	}
}

void	*append_object(t_generic *new_object, t_generic *from_object)
{
	FRAMEWORK_DEBUG(!from_object, NULL_OBJECT_POINTER, "append_object");
	FRAMEWORK_DEBUG(!new_object, NULL_OBJECT_POINTER, "append_object");
	while (from_object->next)
		from_object = from_object->next;
	new_object->prev = from_object;
	return (from_object->next = new_object);
}

void	*new_object(size_t size)
{
	t_generic	*gstruct;

	gstruct = int_memalloc(sizeof(GSTRUCT));
	FRAMEWORK_DEBUG(!gstruct, MALLOC_ERROR, "new_object");
	gstruct->data = int_memalloc(size);
	FRAMEWORK_DEBUG(!gstruct->data, MALLOC_ERROR, "new_object");
	gstruct->size = size;
	return (gstruct);
}

void	*get_data_pointer(t_generic *object, size_t size)
{
	FRAMEWORK_DEBUG(!object, NULL_OBJECT_POINTER, "get_data_pointer");
	FRAMEWORK_DEBUG(object->size != size,
		INVALID_DATA_SIZE, "get_data_pointer");
	FRAMEWORK_DEBUG(!object->data, NULL_DATA_POINTER, "get_data_pointer");
	return (object->size == size ? object->data : NULL);
}
