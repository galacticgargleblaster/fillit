/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/08 15:52:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>

/*
**	A tetronimo represented in fillit format consists of 16 chars + 4 newlines
*/

#define TETROMINO_FORMAT_N_BYTES (16 + 4)
#define MAX_N_TETROMINOES 26

#define Y(idx) (idx / (T_BOUND_SIZE + 1))
#define X(idx) (idx % (T_BOUND_SIZE + 1))
#define IS_VALID_TETROMINO_CHR(c) ((c == EMPTY) || (c == FILLED))

/*
**	If there are exactly four shaded regions, and if every shaded region
**	has at least one neighbor, it's a tetromino.
*/

static int		is_tetromino(t_shape *shape)
{
	(void)shape;
	return (1);
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
	int		idx;

	idx = -1;
	if ((shape = new_shape()) == NULL)
		return (PARSE_ERROR);
	while (++idx < TETROMINO_FORMAT_N_BYTES)
	{
		if (IS_END_OF_LINE(idx) && buf[idx] != '\n')
			RETURN(PARSE_ERROR, "no newline found at row end");
		else if (IS_VALID_TETROMINO_CHR(buf[idx]))
			(*shape)[Y(idx)][X(idx)] = buf[idx];
		else if (IS_END_OF_LINE(idx) && buf[idx] == '\n')
			;
		else
			RETURN(PARSE_ERROR, "invalid char within shape");
	}
	if (!(is_tetromino(shape)))
		return (PARSE_ERROR);
	*shape_ptr = shape;
	return (PARSE_SUCCESS);
}

static int		get_next_tetromino_from_fd(int fd, t_list **tet_list)
{
	char		buf[TETROMINO_FORMAT_N_BYTES];
	char		c;
	t_shape		*shape;
	t_shape		**shape_ptr;
	ssize_t		read_returned;
	t_tetromino *new_tet;

	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	read_returned = read(fd, buf, TETROMINO_FORMAT_N_BYTES);
	if (read_returned == 0)
		return (READ_COMPLETE);
	if (read_returned != TETROMINO_FORMAT_N_BYTES)
		RETURN(READ_ERROR, "read() failed");
	if ((read(fd, &c, 1) == 1) && c != '\n')
		RETURN(READ_ERROR, "no separating newline found");
	shape = NULL;
	shape_ptr = &shape;
	if (parse_shape(buf, shape_ptr) == PARSE_ERROR)
		return (READ_ERROR);
	else if (*shape_ptr == NULL)
		return (READ_COMPLETE);
	if ((new_tet = new_tetromino(*shape_ptr)) == NULL)
		return (READ_ERROR);
	ft_lstaddback(tet_list, ft_lstnewlink(new_tet));
	return (READ_OK);
}

int				read_tetrominoes_from_fd(int fd, t_list **tet_list)
{
	int	status;

	while (ft_lstlen(tet_list) <= MAX_N_TETROMINOES)
	{
		status = get_next_tetromino_from_fd(fd, tet_list);
		if (status == READ_ERROR)
			return (READ_ERROR);
		if (status == READ_COMPLETE)
			break ;
	}
	if (ft_lstlen(tet_list) == 0)
		RETURN(READ_ERROR, "no tetrominoes found");
	else
		return (READ_COMPLETE);
}
