/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/12 17:59:13 by marvin           ###   ########.fr       */
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

#endif

t_board		*compose_board(t_list *guess_list)
{
	t_board *board;
	t_guess	*guess;
	signed char x;
	signed char y;

	board = new_board();
	while (guess_list)
	{
		guess = (t_guess *)(guess_list->content);
		y = guess->tet->y_min;	
		while (y <= guess->tet->y_max)
		{
			x = guess->tet->x_min;
			while (x <= guess->tet->x_max)
			{
				if ((*guess->tet->shape)[y][x] == FILLED)
					(*board)[guess->coord.y + y][guess->coord.x + x] = guess->tet->label;
				x++;
			}
			y++;
		}
		guess_list = guess_list->next;
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
			#ifdef COLORS
			ft_putstr((char*)get_color_for_char(c));
			#endif
			ft_putchar(c);
			#ifdef COLORS
			ft_putstr(RESET);
			#endif
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}