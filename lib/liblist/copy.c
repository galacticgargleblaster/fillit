/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:46:49 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 14:34:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

/*
**===========================================================================**
**	returns a shallow copy
**===========================================================================**
*/

t_doubly_linked_list	*list_copy(const t_doubly_linked_list *list)
{
	t_doubly_linked_list	*new_list;
	t_element_container		*tmp;

	new_list = new_doubly_linked_list();
	tmp = list->tail;
	while (tmp)
	{
		list_push_head(new_list, tmp->element);
		tmp = tmp->next;
	}
	return (new_list);
}

/*
**===========================================================================**
**	user-supplied copying function
**===========================================================================**
*/

t_doubly_linked_list	*list_deepcopy(const t_doubly_linked_list *list,
										void *copy_element(void *))
{
	t_doubly_linked_list	*new_list;
	t_element_container		*tmp;

	new_list = new_doubly_linked_list();
	tmp = list->tail;
	while (tmp)
	{
		list_push_head(new_list, copy_element(tmp->element));
		tmp = tmp->next;
	}
	return (new_list);
}
