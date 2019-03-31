/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:13:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	Check for collisions with a list of already placed tetrominoes, and with
**	the board boundaries.
*/

static int			guess_fits_in_context(const t_guess *new_guess, const t_solver_context *c)
{
	t_element_container	*existing_guesses; 

	existing_guesses = c->guesses->tail;
	if (fits_within_board_of_size(new_guess, c->sidelength))
	{
		while (existing_guesses)
		{
			if (guesses_intersect((t_guess *)(existing_guesses->element), new_guess))
				return (0);
			existing_guesses = existing_guesses->next;
		}	
		return (1);
	}
	return (0);
}

/*
**	If the x, y coordinates of the context have reached the of the board,
**	the context is considered exhausted
*/

t_status			increment_x_y_coordinates(t_solver_context *c)
{
	if (c->coord.x < c->sidelength)
	{
		c->coord.x++;
		return (OK);
	}
	else if (c->coord.y < c->sidelength)
	{
		c->coord.x = 0;
		c->coord.y++;
		return (OK);
	}
	else
		return (EXHAUSTED);
}

/*
**	Given an existing context, namely:
**	- remaining_tet:	list of tetrominoes that need placing
**	- guesses:			list of guesses -- placed tetrominoes
**	- coord:			x, y where the next tetromino will be placed
**	- sidelength:		the board sidelength
**
**	returns a new context in which the next remaining tetromino has been placed.
**	if the next remaining tetromino cannot be placed, returns NULL
*/

t_solver_context	*fork_context(t_solver_context *parent_context)
{
	t_guess				*next_guess;
	t_solver_context	*forked_context;

	next_guess = new_guess(0, 0, list_get_head(parent_context->remaining_tet));
	while (1)
	{
		next_guess->coord = parent_context->coord;
		if (guess_fits_in_context(next_guess, parent_context))
		{
			forked_context = clone_context((const t_solver_context*)parent_context);
			list_pop_head(forked_context->remaining_tet);
			list_push_head(forked_context->guesses, next_guess);
			increment_x_y_coordinates(parent_context);
			return (forked_context);
		}
		if (EXHAUSTED == increment_x_y_coordinates(parent_context))
			break;
	}
	free(next_guess);
	return (NULL);
}
