/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/14 11:13:20 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	Calculate the edges of the rectangle that bounds this guess	
*/

static char left_edge(t_guess *g)
{
	return ((g->coord.x) + (g->tet->x_min));
}

static char right_edge(t_guess *g)
{
	return ((g->coord.x) + (g->tet->x_max));
}

static char top_edge(t_guess *g)
{
	return ((g->coord.y) + (g->tet->y_min));
}

static char bottom_edge(t_guess *g)
{
	return ((g->coord.y) + (g->tet->y_max));
}

/*
**          TOP
**          EDGE
**          (y==1)
**
**        	....
**   LEFT  	##..   RIGHT
**   EDGE  	.#..   EDGE 
**  (x==0)	.#..  (x==1)
**
**          BOTTOM
**          EDGE 
**          (y==3)
*/

int		intersects_with(t_guess *a, t_guess *b)
{
	unsigned char	x;
	unsigned char	y;

	if ((left_edge(b) > right_edge(a)) || (right_edge(b) < left_edge(a)) ||
		(top_edge(b) > bottom_edge(a)) || (bottom_edge(b) < top_edge(a)))
		return (0);
	else
	{
		y = MAX(top_edge(a), top_edge(b));
		while (y < MIN(bottom_edge(a), bottom_edge(b)))
		{
			x = MAX(left_edge(a), left_edge(b));
			while (x < MIN(right_edge(a), right_edge(b)))
			{
				if (((*a->tet->shape)[y - a->coord.y][x - a->coord.x] == FILLED) &&
					((*b->tet->shape)[y - b->coord.y][x - b->coord.x] == FILLED))
					return (1);
				x++;
			}
			y++;
		}
	}
	return (0);
}

int		fits_within_board_of_size(t_guess *g, unsigned char sidelength)
{
	return ((right_edge(g) <= sidelength) && (left_edge(g) >= 0) &&
			(bottom_edge(g) <= sidelength) && (top_edge(g) >= 0));
}

/*
**	Check for collisions with a list of already placed tetrominoes, and with
**	the board boundaries.
*/

int		fits_on_board(t_guess *new_guess, t_list* existing_guess,
						unsigned char sidelength)
{
	if (fits_within_board_of_size(new_guess, sidelength))
	{
		while (existing_guess)
		{
			if (intersects_with((t_guess *)(existing_guess->content), new_guess))
				return (0);
			existing_guess = existing_guess->next;
		}	
		return (1);
	}
	return (0);
}

#define	INITIAL_BOARD_SIDELENGTH 2

		#include "stdio.h"
int		naive_solve(t_list *tet_list)
{
	t_board	*board;
	t_guess *guess;
	t_list *existing_guess = NULL;
	unsigned char x = 0;
	unsigned char y = 0; 
	unsigned char sidelength = 2;
	
	while (tet_list)
	{
		y = 0;
		while (tet_list && y < sidelength)
		{
			x = 0;
			while (tet_list && x < sidelength)
			{
				guess = new_guess(x, y, (t_tetromino *)(tet_list->content));
				if (fits_on_board(guess, existing_guess, sidelength))
				{
					printf("guess: %p\t, x: %d\t y: %d\n", guess, guess->coord.x, guess->coord.y);
					existing_guess = ft_lstpush(existing_guess, ft_lstnewlink(guess));
					printf("guess list at: %p\n", existing_guess);
					tet_list = tet_list->next;
				}
				else
					free(guess);
				x++;
			}
			y++;
		}
		sidelength++;
	}	
	board = compose_board(existing_guess);
	print_board(board, sidelength);
	return (0);
}
