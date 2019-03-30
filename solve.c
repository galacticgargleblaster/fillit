/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 03:01:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	
*/
#include <stdio.h>
static int		guesses_intersect(const t_guess *a, const t_guess *b)
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

static int		fits_within_board_of_size(const t_guess *g, unsigned char sidelength)
{
	return ((g->tet->max.x + g->coord.x < sidelength) &&
			(g->tet->max.y + g->coord.y < sidelength));
}

/*
**	Check for collisions with a list of already placed tetrominoes, and with
**	the board boundaries.
*/

static int		guess_fits_in_context(const t_guess *new_guess, const t_solver_context *c)
{
	t_element_container	*existing_guesses; 

	existing_guesses = c->guesses->head;
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


void				*copy_guess(void *g_ptr)
{
	t_guess	*guess;

	guess = (t_guess *)g_ptr;
	return (new_guess(guess->coord.x, guess->coord.y, guess->tet));
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


/*
**	If the x, y coordinates of the context have reached the of the board,
**	the context is considered exhausted
*/

t_status	increment_x_y_coordinates(t_solver_context *c)
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
#include <stdio.h>

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
			printf("Placing %c at %d, %d\n", next_guess->tet->label, next_guess->coord.x, next_guess->coord.y);
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

unsigned char	minimum_board_sidelength_for_n_tetrominoes(size_t n)
{
	size_t			n_cells;
	unsigned char	sidelength;
	
	n_cells = n * 4;
	sidelength = 2;
	while (sidelength * sidelength < n_cells)
		sidelength++;
	return (sidelength);
}

/*
**	Starting with a single context, the current context forks into two contexts
**	whenever it's possible for a tetromino to be placed.  One of the contexts
**	represents the board if the tetromino was placed.  The other context
**	represents the board if the tetromino was not placed.
**
**	To illustrate this, here's an example with a pair of bitominos:
**	bitominoes:
**	##	#.
**	..	#.
**
**	Initial board, x indicates context's current position
**	0:
**	x.
**	..
**
**	1: A bitomino is placed, a second context is forked and advanced:
**	##	.x
**	..	..
**
**	2: there's no room to place the next tetromino in the 0th context,
**	so that context is destroyed. 
**	.x
**	..
**
**	3: the zeroth bitomino is placed in the next available spot.  The context
**	is forked.
**	..	..
**	##	.x
**
**	4: the first bitomino cannot fit in the zeroth context, so the context is
**	destroyed
**	..
**	.x
**
**	5: the first bitomino cannot fit in the zeroth context, so it's destroyed.
**	Because no contexts remain, and no solution has yet been found, a new
**	context of sidelength 3 is created:
**	x..
**	...
**	...
**
**	6: the first bitomino is placed, and the context is forked:
**	##.	.x.
**	...	...
**	...	...
**
**	7: the next bitomino is placed, the board is solved because there remain
**	no unplaced bitominos
**	###	.x.
**	..#	...
**	...	...
*/

t_solver_context *naive_solve(t_doubly_linked_list *tet_list)
{
	t_doubly_linked_list *contexts;
	t_solver_context	*context;
	t_solver_context	*next_context;
	unsigned char	sidelength;
	
	sidelength = minimum_board_sidelength_for_n_tetrominoes(tet_list->size);
	contexts = new_doubly_linked_list();
	list_push_head(contexts, new_context(list_copy(tet_list), new_doubly_linked_list(), sidelength));
	while (1)
	{
		context = list_get_head(contexts);
		print_context(context);
		if (list_is_empty(context->remaining_tet))
			return (context);
		else if ((next_context = fork_context(context)))
			list_push_head(contexts, next_context);
		else
			destroy_context(list_pop_head(contexts));
		
		if (list_is_empty(contexts))
		{
			sidelength++;
			DMSG(ft_strjoin("Growing sidelength to ", ft_itoa(sidelength)));
			context = new_context(list_copy(tet_list), new_doubly_linked_list(), sidelength);
		}
	}	
}
