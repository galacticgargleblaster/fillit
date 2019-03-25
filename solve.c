/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 00:42:22 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>

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
	return ((g->tet->max.x <= sidelength) && (g->coord.x >= 0) &&
			(g->tet->max.y <= sidelength) && (g->coord.y >= 0));
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

#include "stdio.h"
int		naive_solve_recursively(t_doubly_linked_list *tet_list,
								t_doubly_linked_list *guesses, unsigned char sidelength)
{
	t_guess *guess;

	if (tet_list->size == 0)
		return (1);
	guess = new_guess(0, 0, (t_tetromino *)(list_pop_head(tet_list)));
	while (tet_list->size && guess->coord.y < sidelength)
	{
		guess->coord.x = 0;
		while (tet_list->size && guess->coord.x < sidelength)
		{
			if (fits_on_board(guess, guesses, sidelength))
			{
				list_push_head(guesses, guess);
				if (naive_solve_recursively(tet_list, guesses, sidelength))
					return (1);
			}
			else
			{
				list_push_head(tet_list, guess->tet);
				free(guess);
			}
			guess->coord.x++;
		}
		guess->coord.y++;
	}
	return (0);
}

int		naive_solve(t_doubly_linked_list *tet_list)
{
	t_board	*board;
	t_doubly_linked_list *guesses;
	unsigned char sidelength = 2;
	
	guesses = new_doubly_linked_list();
	while (tet_list->size)
	{
		if (naive_solve_recursively(tet_list, guesses, sidelength))
			break;
		sidelength++;
		DMSG(ft_strjoin("Growing sidelength to ", ft_itoa(sidelength)));
	}	
	board = compose_board(guesses);
	print_board(board, sidelength);
	return (0);
}
