/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/07 15:35:50 by marvin           ###   ########.fr       */
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

typedef	char	t_shape[T_BOUND_SIZE][T_BOUND_SIZE];

typedef struct	s_tetromino
{
	t_shape	shape;
	size_t	x_pos;
	size_t	y_pos;
}				t_tetromino;

# define READ_ERROR -1
# define READ_OK 0
# define READ_COMPLETE 1

int				read_tetrominoes_from_fd(int fd, t_list **tet_list);

#endif
