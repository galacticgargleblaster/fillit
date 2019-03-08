/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/07 18:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"

int		fits_on_board(t_board board, t_tetromino *tetromino)
{

}

#define	INITIAL_BOARD_SIDELENGTH 2

int		naive_solve_inner(t_list *tet_list, t_board board)
{

}

int		naive_solve(t_list *tet_list)
{
	t_board	board;
	size_t	i;

	i = 0;
	while (i < MAX_BOARD_SIDELENGTH)
		ft_bzero(board[i++], MAX_BOARD_SIDELENGTH);
	naive_solve_inner(tet_list, board);
}