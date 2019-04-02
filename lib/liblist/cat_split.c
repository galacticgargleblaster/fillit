/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:46:49 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 14:34:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

/*
**===========================================================================**
**	concatenates b's contents to the tail end of a, then frees b
**===========================================================================**
*/

t_doubly_linked_list	*list_cat(t_doubly_linked_list *a,
									t_doubly_linked_list *b)
{
	if (a->size && b->size)
	{
		a->tail->prev = b->head;
		b->head->next = a->tail;
		a->tail = b->tail;
		a->size += b->size;
		free(b);
	}
	return (a);
}
