/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:35:32 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "lib/liblist/liblist.h"

# ifdef DEBUG
#  define DEBUG_MESSAGE(msg) (ft_putstr_fd(ft_strjoin(msg, "\n"), 2))
#  define PUT_ERR(msg) (ft_putstr_fd(ft_strjoin(msg, "\n"), 2))
#  define DO_IF_DEBUG(x) (x)
# else
#  define DEBUG_MESSAGE(msg)
#  define PUT_ERR(msg)
#  define DO_IF_DEBUG(x)
# endif

# define RETURN(what, why)({PUT_ERR(why); return (what);})
# define EMPTY '.'
# define FILLED '#'
# define T_BOUND_SIZE 4
# define MAX_BOARD_SIDELENGTH (26 * 4)

/*
**	Is this a reasonable way to represent status codes?
**	what makes this better or worse than a preprocessor definition?
*/

typedef enum			e_status
{
	ERROR = -1,
	OK,
	COMPLETE,
	EXHAUSTED
}						t_status;

typedef	struct			s_coordinate
{
	signed char	x;
	signed char	y;
}						t_coordinate;

/*
**	A tetromino is compactly described by a set of four (x, y) coordinates
**
**	For example:
**
**	#...
**	#...
**	##..
**	....
**
**	is represented by the set [(0, 0), (0, 1), (0, 2), (1, 2)]
**
**	this happens to fit nicely into 8 bytes
*/

typedef t_coordinate	t_shape[4];

typedef struct			s_tetromino
{
	t_shape			shape;
	t_coordinate	max;
	signed char		label;
}						t_tetromino;

typedef char			t_board[MAX_BOARD_SIDELENGTH][MAX_BOARD_SIDELENGTH];

/*
**	guess.c
*/

/*
**	A guess represents a placement of a tetromino at a set of coordinates.
**	A single tetromino may have many possible guesses about its position,
**	as such, multiple guesses may point to the same tetromino.
*/

typedef struct			s_guess
{
	t_tetromino		*tet;
	t_coordinate	coord;
}						t_guess;

unsigned char			abs_x(const t_guess *g, unsigned char i);
unsigned char			abs_y(const t_guess *g, unsigned char i);
int						guesses_intersect(const t_guess *a, const t_guess *b);
int						fits_within_board_of_size(const t_guess *g,
							unsigned char sidelength);
void					*copy_guess(void *g_ptr);

/*
**	parse.c
*/

t_status				read_tetrominoes_from_fd(int fd,
										t_doubly_linked_list *tet_list);

/*
**	constructors.c
*/

t_shape					*new_shape(void);
t_tetromino				*new_tetromino(t_shape shape);
t_guess					*new_guess(unsigned char x, unsigned char y,
									t_tetromino *t);
t_board					*new_board(void);

/*
**	context.c
*/

/*
**	A solver context stores the same information that might exist in the
**	stack frames of a recursive solution.
**
**	- remaining_tet:	list of tetrominoes that need placing
**	- guesses:			list of guesses -- placed tetrominoes
**	- coord:			x, y where the next tetromino may be placed
**	- sidelength:		the board sidelength
*/

typedef struct			s_solver_context
{
	t_doubly_linked_list	*remaining_tet;
	t_doubly_linked_list	*guesses;
	t_coordinate			coord;
	unsigned char			sidelength;
}						t_solver_context;

t_solver_context		*fork_context(t_solver_context *parent_context);
t_solver_context		*new_context(t_doubly_linked_list *tet_list,
					t_doubly_linked_list *guesses, unsigned char sidelength);
t_solver_context		*clone_context(const t_solver_context *context);
void					destroy_context(t_solver_context *context);

/*
**	solve.c
*/

t_solver_context		*naive_solve(t_doubly_linked_list *tet_list);

/*
**	print.c
*/

void					print_board(t_board *board, unsigned char sidelength);
t_board					*compose_board(t_doubly_linked_list *guess_list);
void					print_tetrominoes(t_doubly_linked_list *tet_list);
void					print_context(t_solver_context *context);

/*
**	debug.c
*/

void					fillit_putchar(char c);

#endif
