/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:35:59 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

void	print_tetromino(t_tetromino *tet)
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	i;
	char			c;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			c = EMPTY;
			i = 0;
			while (i < 4)
			{
				if (tet->shape[i].x == x && tet->shape[i].y == y)
					c = tet->label;
				i++;
			}
			fillit_putchar(c);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

void	print_tetrominoes(t_doubly_linked_list *tet_list)
{
	t_element_container	*tmp;

	tmp = tet_list->head;
	while (tmp)
	{
		print_tetromino((t_tetromino *)tmp->element);
		ft_putchar('\n');
		tmp = tmp->prev;
	}
}

t_board	*compose_board(t_doubly_linked_list *guess_list)
{
	t_board			*board;
	t_guess			*guess;
	unsigned char	i;
	unsigned char	j;

	board = new_board();
	i = 0;
	while (i < guess_list->size)
	{
		guess = (t_guess *)(list_get_index(guess_list, i));
		j = 0;
		while (j < 4)
		{
			(*board)[abs_y(guess, j)][abs_x(guess, j)] = guess->tet->label;
			j++;
		}
		i++;
	}
	return (board);
}

void	print_board(t_board *board, unsigned char sidelength)
{
	unsigned char x;
	unsigned char y;
	unsigned char c;

	sidelength = MIN(sidelength, MAX_BOARD_SIDELENGTH);
	y = 0;
	while (y < sidelength)
	{
		x = 0;
		while (x < sidelength)
		{
			c = (*board)[y][x];
			fillit_putchar(c);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
