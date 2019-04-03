/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetromino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/04/02 15:02:23 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

static void	move_tetromino_to_upper_left(t_tetromino *tet)
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
	move_tetromino_to_upper_left(tet);
	tet->label = 'A' + g_label;
	g_label++;
	return (tet);
}
