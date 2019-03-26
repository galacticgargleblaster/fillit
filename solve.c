/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 19:37:35 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	
*/

static int		guesses_intersect(t_guess *a, t_guess *b)
{
	unsigned char	i;
	unsigned char	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while(j < 4)
		{
			if (absolute_x(a, i) == absolute_x(b, j) &&
				absolute_y(a, i) == absolute_y(b, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int		fits_within_board_of_size(t_guess *g, unsigned char sidelength)
{
	return ((g->tet->max.x < sidelength) && (g->coord.x >= 0) &&
			(g->tet->max.y < sidelength) && (g->coord.y >= 0));
}

/*
**	Check for collisions with a list of already placed tetrominoes, and with
**	the board boundaries.
*/

static int		fits_on_board(t_guess *new_guess, t_doubly_linked_list* guesses,
						unsigned char sidelength)
{
	t_element_container	*guess_container; 

	guess_container = guesses->head;
	if (fits_within_board_of_size(new_guess, sidelength))
	{
		while (guess_container)
		{
			if (guesses_intersect((t_guess *)(guess_container->element), new_guess))
				return (0);
			guess_container = guess_container->next;
		}	
		return (1);
	}
	return (0);
}

#define	INITIAL_BOARD_SIDELENGTH 2

static inline t_tetromino *get_next_unplaced_tetromino(t_doubly_linked_list *tet_list,
														unsigned char tet_idx,
														t_doubly_linked_list *guesses)
{
	unsigned char guess_idx;
	unsigned char match_exists;
	t_tetromino		*tmp;

	while (tet_idx < tet_list->size)
	{
		guess_idx  = 0;
		match_exists = 0;
		tmp = ((t_tetromino *)list_get_index(tet_list, tet_idx));
		while (guess_idx < guesses->size)
		{
			if (((t_guess *)list_get_index(guesses, guess_idx))->tet == tmp)
			{
				match_exists = 1;
				break;
			}
			guess_idx++;
		}
		if (!match_exists)
			return (tmp);
		tet_idx++;
	}
	return (NULL);
}

#include "stdio.h"
int		naive_solve_recursively(t_doubly_linked_list *tet_list, 
								t_doubly_linked_list *guesses, unsigned char sidelength)
{
	t_guess 	*guess;
	t_tetromino *tmp;
	unsigned char tet_idx;

	tet_idx = 0;
	while ((tmp = get_next_unplaced_tetromino(tet_list, tet_idx, guesses)))
	{
		guess = new_guess(0, 0, tmp);
		while (guess->coord.y + guess->tet->max.y < sidelength)
		{
			guess->coord.x = 0;
			while (guess->coord.x + guess->tet->max.x < sidelength)
			{
				if (fits_on_board(guess, guesses, sidelength))
				{
					
					list_push_head(guesses, guess);
					if (naive_solve_recursively(tet_list, guesses, sidelength))
					{
					printf("%slabel %c fits on board at x: %d\t y: %d\t with  %zu guesses\n", ft_strnew(sidelength), tmp->label, guess->coord.x, guess->coord.y, guesses->size);
						return (1);
					}
					else
						list_pop_head(guesses);
				}
				guess->coord.x++;
			}
			guess->coord.y++;
		}
		free(guess);
		tet_idx++;
	}
	if (guesses->size == tet_list->size)
		return (1);
	return (0);
}

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

void				destroy_context(t_solver_context *context)
{
	if (context->guesses)
		delete_doubly_linked_list(context->guesses, free);
	if (context->remaining_tet)
		delete_doubly_linked_list(context->remaining_tet, NULL);
	free(context);
}

/*
**	Returns the next valid step in the current context, else NULL
*/

t_solver_context	*get_next_context(t_solver_context *old_context)
{
	t_tetromino	*tet;
	t_guess		*guess;
	t_solver_context *next_context;

	while (!list_is_empty(old_context->remaining_tet))
	{
		tet = list_get_head(old_context->remaining_tet);
		guess = new_guess(old_context->coord.x, old_context->coord.y, tet);
		while (guess->coord.y + guess->tet->max.y < old_context->sidelength)
		{
			guess->coord.x = 0;
			while (guess->coord.x + guess->tet->max.x < old_context->sidelength)
			{
				if (fits_on_board(guess, old_context->guesses, old_context->sidelength))
				{
					next_context = new_context(list_copy(old_context->remaining_tet), 
										new_doubly_linked_list(), old_context->sidelength);
					list_push_head(next_context->guesses, guess);
					old_context->coord.y = guess->coord.y;
					old_context->coord.x = guess->coord.x + 1;
					return (next_context);
				}
				guess->coord.x++;
			}
			guess->coord.y++;
		}
		list_pop_head(old_context->remaining_tet);
	}
	free(guess);
	return (NULL);
}

t_solver_context *naive_solve(t_doubly_linked_list *tet_list)
{
	t_doubly_linked_list *contexts;
	t_solver_context	*context;
	unsigned char	sidelength;
	
	sidelength = 2;
	contexts = new_doubly_linked_list();
	list_push_head(contexts, new_context(list_copy(tet_list), new_doubly_linked_list(), sidelength));
	while (1)
	{
		context = get_next_context((t_solver_context *)list_get_head(contexts));
		if (context == NULL)
			destroy_context(list_pop_head(contexts));
		else if (list_is_empty(context->remaining_tet))
			return (context);
		else
			list_push_head(contexts, context);
		
		if (list_is_empty(contexts))
		{
			sidelength++;
			DMSG(ft_strjoin("Growing sidelength to ", ft_itoa(sidelength)));
			context = new_context(list_copy(tet_list), new_doubly_linked_list(), sidelength);
			if (context)
				list_push_head(contexts, context);
			else
				RETURN(NULL, "failed to get new context");
		}
	}	
}
