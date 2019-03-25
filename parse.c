/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/24 22:49:02 by student          ###   ########.fr       */
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
	return ((ABS(a.x - b.x) == 1) || (ABS(a.y - b.y) == 1));
}

/*
**	Checks that the set of four coordinates have at least three adjacencies in total
*/

static int		is_tetromino(t_shape *shape)
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

#define PARSE_ERROR -1
#define PARSE_SUCCESS 0

/*
**	Transforms a string containing what may be a tetromino into a 4x4 char array
**	Returns the char array, or
**	Returns NULL if an error occurs
*/

#define IS_END_OF_LINE(idx) (idx % 5 == 4)

static int		parse_shape(char *buf, t_shape **shape_ptr)
{
	t_shape *shape;
	signed char	idx;
	signed char	shape_idx;

	idx = -1;
	shape_idx = -1;
	if ((shape = new_shape()) == NULL)
		return (PARSE_ERROR);
	while (++idx < TETROMINO_FORMAT_N_BYTES)
	{
		if (IS_END_OF_LINE(idx) && buf[idx] != '\n')
			RETURN(PARSE_ERROR, "no newline found at row end");
		else if (buf[idx] == FILLED)
		{
			if (++shape_idx == 4)
				RETURN(PARSE_ERROR, "More than 4 points in this shape");
			(*shape)[shape_idx].x = AS_X_COORD(idx);
			(*shape)[shape_idx].y = AS_Y_COORD(idx);
		}
		else if (buf[idx] == EMPTY || (IS_END_OF_LINE(idx) && buf[idx] == '\n'))
			continue ;
		else
			RETURN(PARSE_ERROR, "invalid char within shape");
	}
	if (shape_idx != 3 || !(is_tetromino(shape)))
		return (PARSE_ERROR);
	*shape_ptr = shape;
	return (PARSE_SUCCESS);
}

static int		get_next_tetromino_from_fd(int fd,
					t_doubly_linked_list *tet_list)
{
	char		buf[TETROMINO_FORMAT_N_BYTES];
	char		c;
	t_shape		*shape_ptr;
	ssize_t		read_returned;
	t_tetromino *new_tet;

	shape_ptr = NULL;
	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	read_returned = read(fd, buf, TETROMINO_FORMAT_N_BYTES);
	if (read_returned == 0)
		return (READ_COMPLETE);
	if (read_returned != TETROMINO_FORMAT_N_BYTES)
		RETURN(READ_ERROR, "read() failed");
	if ((read(fd, &c, 1) == 1) && c != '\n')
		RETURN(READ_ERROR, "no separating newline found");
	if (parse_shape(buf, &shape_ptr) == PARSE_ERROR)
		return (READ_ERROR);
	else if (shape_ptr == NULL)
		return (READ_COMPLETE);
	if ((new_tet = new_tetromino(*shape_ptr)) == NULL)
		return (READ_ERROR);
	list_push_head(tet_list, new_tet);
	return (READ_OK);
}

int				read_tetrominoes_from_fd(int fd, t_doubly_linked_list *tet_list)
{
	int	status;

	while (tet_list->size <= MAX_N_TETROMINOES)
	{
		status = get_next_tetromino_from_fd(fd, tet_list);
		if (status == READ_ERROR)
			return (READ_ERROR);
		if (status == READ_COMPLETE)
			break ;
	}
	if (tet_list->size == 0)
		RETURN(READ_ERROR, "no tetrominoes found");
	else
		return (READ_COMPLETE);
}
