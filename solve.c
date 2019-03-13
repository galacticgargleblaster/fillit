/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/12 18:57:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

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

// int		naive_solve_inner(t_list *tet_list, t_board board)
// {
// 	while (tet_list)
// 	{
// 		advance_tetromino()
// 		if (fits_on_board(board, (t_tetromino *)(tet_list->content))
// 			naive_solve_inner(tet_list->next, )
// 	}
// }
// 
// int		naive_solve(t_list *tet_list)
// {
// 	t_board	board;
// 	size_t	i;
// 
// 	i = 0;
// 	while (i < MAX_BOARD_SIDELENGTH)
// 		ft_bzero(board[i++], MAX_BOARD_SIDELENGTH);
// 	naive_solve_inner(tet_list, board);
// }