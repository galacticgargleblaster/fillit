/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/04/02 12:04:40 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/liblist/liblist.h"
#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>

/*
**	A tetronimo represented in fillit format consists of 16 chars + 4 newlines
*/

#define TETROMINO_FORMAT_N_BYTES (16 + 4)
#define MAX_N_TETROMINOES 26

#define AS_Y_COORD(idx) (idx / (T_BOUND_SIZE + 1))
#define AS_X_COORD(idx) (idx % (T_BOUND_SIZE + 1))
#define IS_VALID_TETROMINO_CHR(c) ((c == EMPTY) || (c == FILLED))
#define ABS(x) ((x) < 0 ? -(x) : (x))

static inline int	is_adjacent(t_coordinate a, t_coordinate b)
{
	return ((ABS(a.x - b.x) == 1) && ((a.y - b.y) == 0)) ||
			(((a.x - b.x) == 0) && (ABS(a.y - b.y) == 1));
}

/*
**	Checks that the set of four coordinates have at least three adjacencies
**	in total
*/

static int			is_tetromino(t_shape *shape)
{
	unsigned char	adjacencies;
	unsigned char	coord_a;
	unsigned char	coord_b;

	adjacencies = 0;
	coord_a = 0;
	while (coord_a < (sizeof(t_shape) / sizeof(t_coordinate) - 1))
	{
		coord_b = coord_a + 1;
		while (coord_b < (sizeof(t_shape) / sizeof(t_coordinate)))
		{
			adjacencies += is_adjacent((*shape)[coord_a], (*shape)[coord_b]);
			coord_b += 1;
		}
		coord_a += 1;
	}
	return (adjacencies >= 3);
}

#define ERROR -1
#define SUCCESS 0

/*
**	Transforms a string containing what may be a tetromino into a 4x4 char array
**	Returns the char array, or
**	Returns NULL if an error occurs
*/

#define IS_END_OF_LINE(idx) (idx % 5 == 4)

static int			parse_shape(char *buf, t_shape **shape_ptr)
{
	signed char	buf_idx;
	signed char	shape_idx;

	buf_idx = -1;
	shape_idx = -1;
	if ((*shape_ptr = new_shape()) == NULL)
		return (ERROR);
	while (++buf_idx < TETROMINO_FORMAT_N_BYTES)
	{
		if (IS_END_OF_LINE(buf_idx) && buf[buf_idx] != '\n')
			RETURN(ERROR, "no newline found at row end");
		else if (buf[buf_idx] == FILLED)
		{
			if (++shape_idx == 4)
				RETURN(ERROR, "More than 4 points in this shape");
			(**shape_ptr)[shape_idx].x = AS_X_COORD(buf_idx);
			(**shape_ptr)[shape_idx].y = AS_Y_COORD(buf_idx);
		}
		else if (buf[buf_idx] != EMPTY && !(IS_END_OF_LINE(buf_idx)))
			RETURN(ERROR, "invalid char within shape");
	}
	if (shape_idx != 3 || !(is_tetromino(*shape_ptr)))
		RETURN(ERROR, "shape is not a tetromino");
	return (SUCCESS);
}

static int			get_next_tetromino_from_fd(int fd,
						t_doubly_linked_list *tet_list)
{
	char		buf[TETROMINO_FORMAT_N_BYTES];
	t_shape		*shape_ptr;
	ssize_t		read_returned;
	t_tetromino *new_tet;

	shape_ptr = NULL;
	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	read_returned = read(fd, buf, TETROMINO_FORMAT_N_BYTES);
	if (read_returned == 0)
		return (COMPLETE);
	if (read_returned != TETROMINO_FORMAT_N_BYTES)
		RETURN(ERROR, "read() failed");
	if (parse_shape(buf, &shape_ptr) == ERROR)
		return (ERROR);
	if ((new_tet = new_tetromino(*shape_ptr)) == NULL)
		return (ERROR);
	list_push_tail(tet_list, new_tet);
	return (OK);
}

int					read_tetrominoes_from_fd(int fd,
						t_doubly_linked_list *tet_list)
{
	int		status;
	char	c;
	ssize_t separating_nl_exists;

	separating_nl_exists = 0;
	while (tet_list->size <= MAX_N_TETROMINOES)
	{
		status = get_next_tetromino_from_fd(fd, tet_list);
		if (status == ERROR)
			return (ERROR);
		if (0 > ((separating_nl_exists = read(fd, &c, 1))))
			RETURN(ERROR, "failed to read separator char");
		if ((separating_nl_exists == 1) && c != '\n')
			RETURN(ERROR, "invalid separator char found between tet");
		if (status == OK && !separating_nl_exists)
			break ;
		else if (status == COMPLETE)
			RETURN(ERROR, "redundant newlines found at EOF");
	}
	if (tet_list->size == 0)
		RETURN(ERROR, "no tetrominoes found");
	else
		return (COMPLETE);
}
