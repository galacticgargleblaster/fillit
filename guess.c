/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:42:20 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

unsigned char	abs_x(const t_guess *g, unsigned char i)
{
	return (g->coord.x + g->tet->shape[i].x);
}

unsigned char	abs_y(const t_guess *g, unsigned char i)
{
	return (g->coord.y + g->tet->shape[i].y);
}

int				guesses_intersect(const t_guess *a, const t_guess *b)
{
	unsigned char	i;
	unsigned char	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (abs_x(a, i) == abs_x(b, j) &&
				abs_y(a, i) == abs_y(b, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				fits_within_board_of_size(const t_guess *g,
											unsigned char sidelength)
{
	return ((g->tet->max.x + g->coord.x < sidelength) &&
			(g->tet->max.y + g->coord.y < sidelength));
}
