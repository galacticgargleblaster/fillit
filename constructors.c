/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/08 13:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	Allocates and initializes memory to store the shape of a tetromino
*/

t_shape	*new_shape(void)
{
	t_shape *shape;

	if (((shape = malloc(sizeof(t_shape)))) == NULL)
		RETURN(NULL, "malloc failed");
	ft_bzero(shape, sizeof(t_shape));
	return (shape);
}

/*
**	
*/

static void	init_tet_min_max(t_tetromino *tet)
{
	int			x;
	int			y;

	tet->x_min = T_BOUND_SIZE;
	tet->x_max = 0;
	tet->y_min = T_BOUND_SIZE;
	tet->y_max = 0;
	x = -1;
	y = -1;
	while (++x < T_BOUND_SIZE)
	{
		while (++y < T_BOUND_SIZE)
		{
			if (*(tet->shape)[x][y] == FILLED)
			{
				tet->x_min = MIN(tet->x_min, x);
				tet->x_max = MAX(tet->x_max, x);
				tet->y_min = MIN(tet->y_min, y);
				tet->y_max = MAX(tet->y_max, y);
			}
		}
	}
}

t_tetromino	*new_tetromino(t_shape* shape)
{
	static unsigned char	label;
	t_tetromino				*tet;

	tet = malloc(sizeof(t_tetromino));
	if (tet == NULL)
		return (NULL);
	tet->shape = shape;
	tet->coord.x = 0;
	tet->coord.y = 0;
	init_tet_min_max(tet);
	tet->label = 'A' + label;
	return (tet);
}

t_board		*new_board(void)
{
	t_board	*board;
	int		row;

	board = malloc(sizeof(t_board));
	if (board == NULL)
		return (NULL);
	row = 0;
	while (row < MAX_BOARD_SIDELENGTH)
	{
		ft_memset(*board[row], EMPTY, MAX_BOARD_SIDELENGTH);
		row++;
	}
	return (board);
}