/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/08 16:05:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

/*
**  https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
*/

#define CYAN "\033[7;96m"
#define YELLOW "\033[7;93m"
#define MAGENTA "\033[7;95m"
#define BLUE "\033[7;94m"
#define ORANGE "\033[7;33m"
#define GREEN "\033[7;32m"
#define RED "\033[7;31m"


t_board *compose_board(t_list *tet_list)
{
	t_board *board;
	t_tetromino *tet; 
	signed char x;
	signed char y;

	board = new_board();
	while (tet_list)
	{
		tet = AS_TET(tet_list);
		y = tet->y_min;	
		while (y <= tet->y_max)
		{
			x = tet->x_min;
			while (x <= tet->x_max)
			{
				if ((*tet->shape)[y][x] == FILLED)
					(*board)[tet->coord.y + y][tet->coord.x + x] = tet->label;
				x++;
			}
			y++;
		}
		tet_list = tet_list->next;
	}
	return (board);
}

void	print_board(t_board *board)
{
	unsigned char x;
	unsigned char y;

	y = 0;
	while (y < MAX_BOARD_SIDELENGTH)
	{
		x = 0;
		while (x < MAX_BOARD_SIDELENGTH)
		{
			ft_putchar((*board)[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}