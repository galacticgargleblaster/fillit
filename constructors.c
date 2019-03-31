/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:23:38 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

/*
**	Allocates and initializes memory to store the shape of a tetromino
*/

t_shape		*new_shape(void)
{
	t_shape *shape;

	if (((shape = malloc(sizeof(t_shape)))) == NULL)
		RETURN(NULL, "malloc failed");
	ft_bzero(shape, sizeof(t_shape));
	return (shape);
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
