/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/04/03 10:36:30 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

#ifdef DEBUG

/*
**  https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
*/

# define CYAN "\033[7;96m"
# define YELLOW "\033[7;93m"
# define MAGENTA "\033[7;95m"
# define BLUE "\033[7;94m"
# define ORANGE "\033[7;33m"
# define GREEN "\033[7;32m"
# define RED "\033[7;31m"
# define RESET "\033[0m"

const char *const	g_colors[] = {
	CYAN,
	YELLOW,
	MAGENTA,
	BLUE,
	ORANGE,
	GREEN,
	RED,
};

static const char	*get_color_for_char(unsigned char c)
{
	if (c == '.')
		return (RESET);
	return (g_colors[c % (sizeof(g_colors) / sizeof(char **))]);
}

void				print_context(t_solver_context *context)
{
	t_board	*board;
	size_t	i;

	i = 0;
	while (i < context->remaining_tet->size)
	{
		ft_putchar(((t_tetromino *)
					list_get_index(context->remaining_tet, i))->label);
		ft_putchar(' ');
		i++;
	}
	ft_putstr("\n");
	board = compose_board(context->guesses);
	print_board(board, context->sidelength);
}

void				fillit_putchar(char c)
{
	ft_putstr((char*)get_color_for_char(c));
	ft_putchar(c);
	ft_putstr(RESET);
}

#else

void				fillit_putchar(char c)
{
	ft_putchar(c);
}

#endif
