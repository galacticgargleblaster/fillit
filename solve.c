/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/12 00:17:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

/*
**	
*/

#define LEFT_EDGE(tet) (tet->coord.x + tet->x_min)
#define RIGHT_EDGE(tet) (tet->coord.x + tet->x_max)
#define TOP_EDGE(tet) (tet->coord.y + tet->y_min)
#define BOTTOM_EDGE(tet) (tet->coord.y + tet->y_max)

int		intersects_with(t_tetromino *a, t_tetromino *b)
{
	unsigned char	x;
	unsigned char	y;

	if (LEFT_EDGE(b) > RIGHT_EDGE(a) || RIGHT_EDGE(b) < LEFT_EDGE(a) ||
		BOTTOM_EDGE(b) > TOP_EDGE(a) || TOP_EDGE(b) < BOTTOM_EDGE(a))
		return (0);
	else
	{
		y = MAX(BOTTOM_EDGE(a), BOTTOM_EDGE(b));
		while (y < MIN(TOP_EDGE(a), TOP_EDGE(b)))
		{
			x = MAX(LEFT_EDGE(a), LEFT_EDGE(b));
			while (x < MIN(LEFT_EDGE(a), LEFT_EDGE(b)))
			{
				if (((*a->shape)[y - a->coord.y][x - a->coord.x] == FILLED) &&
					((*b->shape)[y - b->coord.y][x - b->coord.x] == FILLED))
					return (1);
				x++;
			}
			y++;
		}
	}
	return (0);
}

int		fits_within_board_of_size(t_tetromino *tet, unsigned char sidelength)
{
	return (tet->coord.x + tet->x_max < sidelength && tet->coord.x + tet->x_min > 0 &&
			tet->coord.y + tet->y_max < sidelength && tet->coord.y + tet->y_min > 0);
}

/*
**	Check for collisions with a list of already placed tetrominoes, and with
**	the board boundaries.
*/

// int		fits_on_board(t_tetromino *tetromino, t_list* existing,
// 						unsigned char sidelength)
// {
// 	while (existing)
// 	{
// 			
// 		existing = existing->next;
// 	}	
// }

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