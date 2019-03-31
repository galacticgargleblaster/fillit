/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:27:57 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

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
	list_push_head(contexts, new_context(list_copy(tet_list),
					new_doubly_linked_list(), sidelength));
	while (1)
	{
		context = list_get_head(contexts);
		DO_IF_DEBUG(print_context(context));
		if (list_is_empty(context->remaining_tet))
			return (context);
		else if ((next_context = fork_context(context)))
			list_push_head(contexts, next_context);
		else
			destroy_context(list_pop_head(contexts));
		
		if (list_is_empty(contexts))
		{
			sidelength++;
			DEBUG_MESSAGE(ft_strjoin("Growing sidelength to ",
							ft_itoa(sidelength)));
			context = new_context(list_copy(tet_list),
						new_doubly_linked_list(), sidelength);
		}
	}	
}
