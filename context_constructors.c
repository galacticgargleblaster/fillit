/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:36:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

t_solver_context	*new_context(t_doubly_linked_list *tet_list,
					t_doubly_linked_list *guesses, unsigned char sidelength)
{
	t_solver_context	*context;

	context = malloc(sizeof(t_solver_context));
	context->remaining_tet = tet_list;
	context->sidelength = sidelength;
	context->guesses = guesses;
	context->coord.x = 0;
	context->coord.y = 0;
	return (context);
}

t_solver_context	*clone_context(const t_solver_context *context)
{
	return (new_context(list_copy(context->remaining_tet),
						list_deepcopy(context->guesses, &copy_guess),
						context->sidelength));
}

void				destroy_context(t_solver_context *context)
{
	delete_doubly_linked_list(context->guesses, free);
	delete_doubly_linked_list(context->remaining_tet, NULL);
	free(context);
}
