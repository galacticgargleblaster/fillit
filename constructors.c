/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/24 23:33:08 by student          ###   ########.fr       */
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

static void	move_shape_to_upper_left(t_tetromino *tet)
{
	unsigned char	i;
	unsigned char	min_x;
	unsigned char	min_y;
	
	i = 0;
	min_x = 3;
	min_y = 3;
	tet->max.x = 0;
	tet->max.y = 0;
	while (i < 4)
	{
		min_x = MIN(min_x, tet->shape[i].x);
		min_y = MIN(min_y, tet->shape[i].y);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tet->shape[i].x = tet->shape[i].x - min_x;
		tet->shape[i].y = tet->shape[i].y - min_y;
		tet->max.x = MAX(tet->max.x, tet->shape[i].x);
		tet->max.y = MAX(tet->max.y, tet->shape[i].y);
		i++;
	}
}

static unsigned char	g_label = 0;

t_tetromino	*new_tetromino(t_shape shape)
{
	t_tetromino				*tet;

	tet = malloc(sizeof(t_tetromino));
	if (tet == NULL)
		return (NULL);
	ft_memcpy(tet->shape, shape, sizeof(t_shape));
	move_shape_to_upper_left(tet);
	tet->label = 'A' + g_label;
	g_label++;
	return (tet);
}

t_guess		*new_guess(unsigned char x, unsigned char y, t_tetromino *t)
{
	t_guess	*guess;

	guess = malloc(sizeof(t_guess));
	if (guess == NULL)
		return (NULL);
	guess->tet = t;
	guess->coord.x = x;
	guess->coord.y = y;
	return (guess);
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
		ft_memset((*board)[row], EMPTY, MAX_BOARD_SIDELENGTH);
		row++;
	}
	return (board);
}
