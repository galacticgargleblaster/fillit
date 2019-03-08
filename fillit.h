/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/07 16:51:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# ifdef DEBUG_MESSAGES
#  define PUT_ERR(msg) (ft_putstr_fd(ft_strjoin(msg, "\n"), 2))
# else
#  define PUT_ERR(msg)
# endif

# ifdef COLORS
# endif

# define RETURN(what, why)({PUT_ERR(why); return (what);})

# define T_BOUND_SIZE 4
# define MAX_BOARD_SIDELENGTH (26 * 4)

typedef	char	t_shape[T_BOUND_SIZE][T_BOUND_SIZE];

typedef struct	s_tetromino
{
	t_shape			*shape;
	unsigned char	x_pos;
	unsigned char	y_pos;
	unsigned char	label;
}				t_tetromino;

typedef char	t_board[MAX_BOARD_SIDELENGTH][MAX_BOARD_SIDELENGTH];

# define READ_ERROR -1
# define READ_OK 0
# define READ_COMPLETE 1

int				read_tetrominoes_from_fd(int fd, t_list **tet_list);

#endif
