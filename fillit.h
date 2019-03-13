/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/12 17:57:26 by marvin           ###   ########.fr       */
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

# define EMPTY '.'
# define FILLED '#'
# define T_BOUND_SIZE 4
# define MAX_BOARD_SIDELENGTH (26 * 4)

typedef	char	t_shape[T_BOUND_SIZE][T_BOUND_SIZE];

typedef	struct	s_coordinate
{
	signed char	x;
	signed char	y;
}				t_coordinate;

/*
**	A tetromino contains a shape and metadata about that shape
**	x_min, .., y_max -- describe the edges of the rectangle that bounds the shape,
**	because no shape occupies the entire 4x4 space.
**	label - 'A', 'B', 'C', 'D', ... depending on the order in which the
**	tetromino was read.
*/

typedef struct	s_tetromino
{
	t_shape			*shape;
	unsigned char	x_min;
	unsigned char	x_max;
	unsigned char	y_min;
	unsigned char	y_max;
	unsigned char	label;
}				t_tetromino;

/*
**	A guess represents a placement of a tetromino at a set of coordinates.
**	A single tetromino may have many possible guesses about its position,
**	as such multiple guesses may point to the same tetromino.
*/

typedef struct	s_guess
{
	t_tetromino		*tet;
	t_coordinate	coord;	
}				t_guess;

typedef char	t_board[MAX_BOARD_SIDELENGTH][MAX_BOARD_SIDELENGTH];

/*
**	parse.c
*/

# define ERROR -1
# define READ_ERROR ERROR
# define READ_OK 0
# define READ_COMPLETE 1

int				read_tetrominoes_from_fd(int fd, t_list **tet_list);

/*
**	constructors.c
*/

t_shape			*new_shape(void);
t_tetromino		*new_tetromino(t_shape *shape);
t_board			*new_board(void);

/*
**	print.c
*/

void			print_board(t_board *board, unsigned char sidelength);
t_board			*compose_board(t_list *tet_list);

#endif
