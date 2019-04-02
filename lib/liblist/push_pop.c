/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:46:49 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 14:32:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void					list_push_head(t_doubly_linked_list *list,
										void *element)
{
	t_element_container	*container;

	container = new_doubly_linked_element_container();
	container->element = element;
	if (list_is_empty(list))
	{
		list->head = container;
		list->tail = container;
	}
	else
	{
		list->head->next = container;
		container->prev = list->head;
		list->head = list->head->next;
	}
	list->size++;
}

void					list_push_tail(t_doubly_linked_list *list,
										void *element)
{
	t_element_container	*container;

	container = new_doubly_linked_element_container();
	container->element = element;
	if (list_is_empty(list))
	{
		list->tail = container;
		list->head = container;
	}
	else
	{
		list->tail->prev = container;
		container->next = list->tail;
		list->tail = list->tail->prev;
	}
	list->size++;
}

void					*list_pop_head(t_doubly_linked_list *list)
{
	void	*element;

	element = NULL;
	if (list_is_empty(list))
		return (NULL);
	else
	{
		element = list->head->element;
		if (list->size > 1)
		{
			list->head = list->head->prev;
			free(list->head->next);
			list->head->next = NULL;
		}
		else
		{
			free(list->head);
			list->head = NULL;
			list->tail = NULL;
		}
		list->size--;
		return (element);
	}
}

void					*list_pop_tail(t_doubly_linked_list *list)
{
	void	*element;

	element = NULL;
	if (list_is_empty(list))
		return (NULL);
	else
	{
		element = list->tail->element;
		if (list->size > 1)
		{
			list->tail = list->tail->next;
			free(list->tail->prev);
			list->tail->prev = NULL;
		}
		else
		{
			free(list->tail);
			list->head = NULL;
			list->tail = NULL;
		}
		list->size--;
		return (element);
	}
}

void					*list_pop_index(t_doubly_linked_list *list, size_t idx)
{
	void				*element;
	t_element_container	*tmp;

	if (list_is_empty(list) || idx > list->size - 1)
		return (NULL);
	else if (idx == 0)
		return (list_pop_tail(list));
	else if (idx == list->size)
		return (list_pop_head(list));
	tmp = list->tail->element;
	while (idx--)
		tmp = tmp->next;
	element = tmp->element;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	list->size--;
	free(tmp);
	return (element);
}
