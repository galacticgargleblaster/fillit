/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 02:39:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

#ifdef COLORS

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
#define RESET "\033[0m"

const char* const g_colors[] = {
	CYAN,
	YELLOW,
	MAGENTA,
	BLUE,
	ORANGE,
	GREEN,
	RED,
};

static const char*	get_color_for_char(unsigned char c)
{
	if (c == '.')
		return (RESET);
	return (g_colors[c % (sizeof(g_colors) / sizeof(char **))]);
}

void ft_putchar_color(char c)
{
	ft_putstr((char*)get_color_for_char(c));
	ft_putchar(c);
	ft_putstr(RESET);
}

#else

void ft_putchar_color(char c)
{
	ft_putchar(c);
}

#endif


void		print_tetromino(t_tetromino *tet)
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
			ft_putchar_color(c);
			x++;
		}
		ft_putchar_color('\n');
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


		#include "stdio.h"
t_board		*compose_board(t_doubly_linked_list *guess_list)
{
	t_board *board;
	t_guess	*guess;
	unsigned char i;
	unsigned char j;

	board = new_board();
	ft_putstr(ft_strjoin(ft_strjoin("Printing ", ft_itoa(guess_list->size)), " guesses\n"));
	i = 0;
	while (i < guess_list->size)
	{
		guess = (t_guess *)(list_get_index(guess_list, i));
		printf("guess: %d\taddr:%p\tx: %d\ty%d\n", i, guess, guess->coord.x, guess->coord.y);
		j = 0;
		while (j < 4)
		{
			(*board)[absolute_y(guess, j)][absolute_x(guess, j)] = guess->tet->label;
			j++;
		}
		i++;
	}
	return (board);
}

void		print_board(t_board *board, unsigned char sidelength)
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
			ft_putchar_color(c);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}


#include <stdio.h>
void		print_context(t_solver_context *context)
{
	t_board	*board;
	
	printf("context with %zu tet remaining: ", context->remaining_tet->size);
	for (size_t i = 0; i < context->remaining_tet->size; i++)
	{
		printf("%c ", ((t_tetromino *)list_get_index(context->remaining_tet, i))->label);
	}
	printf("\n");
	board = compose_board(context->guesses);
	print_board(board, context->sidelength);
}