/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:44:32 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 14:33:48 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

t_doubly_linked_list	*new_doubly_linked_list(void)
{
	t_doubly_linked_list *list;

	list = malloc(sizeof(t_doubly_linked_list));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_element_container		*new_doubly_linked_element_container(void)
{
	t_element_container *container;

	container = malloc(sizeof(t_element_container));
	container->element = NULL;
	container->next = NULL;
	container->prev = NULL;
	return (container);
}

void					delete_doubly_linked_list(t_doubly_linked_list *list,
											void delete_element(void *element))
{
	t_element_container *tmp;

	while (list->size)
	{
		if (delete_element)
			delete_element(list->tail->element);
		tmp = list->tail;
		list->tail = list->tail->next;
		free(tmp);
		list->size--;
	}
	free(list);
}
