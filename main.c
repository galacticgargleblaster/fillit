#include "lib/libft/libft.h"
#include "fillit.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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

/*
**	A tetronimo represented in fillit format consists of 16 chars + 4 newlines
*/
#define TETROMINO_FORMAT_N_BYTES (16 + 4)
#define MAX_N_TETROMINOES 26
#define ERROR(stmt, msg)({ PUTERR(msg); stmt; })
#define INFO(msg) ({ ft_putstr(msg); ft_putchar('\n'); })
#define T_BOUND_SIZE 4
#define Y(idx) (idx / (T_BOUND_SIZE + 1))
#define X(idx) (idx % (T_BOUND_SIZE + 1))
#define IS_VALID_CHR(c) (ft_strchr(".#\n", c ))

/*
**	Allocates and initializes memory to store the shape of a tetromino
*/
t_shape	*new_shape()
{
	t_shape	*shape;
	size_t	row;

	if (((shape = malloc(sizeof(t_shape)))) == NULL)
		ERROR(return (NULL), "malloc failed");
	row = 0;
	while (row < T_BOUND_SIZE)
	{
		ft_bzero((*shape)[row], T_BOUND_SIZE);
		row++;
	}	
	return (shape);
}

/*
**	If there are exactly four shaded regions, and if every shaded region
**	has at least one neighbor, it's a tetromino.
*/
int		is_tetromino(t_shape *shape)
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
int		parse_shape(char *buf, t_shape** shape_ptr)
{
	t_shape *shape;
	int		idx;

	idx = 0;
	if ((shape = new_shape()) == NULL)
		ERROR(return (PARSE_ERROR), "can't get new shape");
	while (idx < TETROMINO_FORMAT_N_BYTES)
	{
		if (NOT(IS_VALID_CHR(buf[idx])))
			ERROR(return (PARSE_ERROR), ft_strjoin("Encountered invalid char: ", ft_strndup(&buf[idx], 1)));
		if (IS_END_OF_LINE(idx))
		{
			if (buf[idx] != '\n')
			ERROR(return (PARSE_ERROR), ft_strjoin("no newline found at x index 4 of row: ", ft_itoa(Y(idx))));
		}
		else
		{
			if (buf[idx] == '\n')
				ERROR(return (PARSE_ERROR), "newline found in wrong position");	
			(*shape)[Y(idx)][X(idx)] = buf[idx];
		}
		idx++;
	}
	if (NOT(is_tetromino(shape)))
		return (PARSE_ERROR);
	*shape_ptr = shape;
	return (PARSE_SUCCESS);
}


/*
**
*/
#define READ_ERROR -1
#define READ_OK 0
#define READ_COMPLETE 1

int		get_next_tetromino_from_fd(int fd, t_list **tet_list)
{
	char	buf[TETROMINO_FORMAT_N_BYTES];
	char	c;
	t_shape *shape;
	t_shape	**shape_ptr;
	ssize_t read_returned;

	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	read_returned = read(fd, buf, TETROMINO_FORMAT_N_BYTES);
	if (read_returned ==  0)
		return (READ_COMPLETE);
	if (read_returned != TETROMINO_FORMAT_N_BYTES)
		ERROR(return (READ_ERROR), "read() failed");
	if ((read(fd, &c, 1) == 1) && c != '\n')
		ERROR(return (READ_ERROR), "no separating newline found");
	shape = NULL;
	shape_ptr = &shape;
	if (parse_shape(buf, shape_ptr) == PARSE_ERROR)
		return (READ_ERROR);
	else if (*shape_ptr == NULL)
		return (READ_COMPLETE);
	ft_lstadd(tet_list, ft_lstnewlink(*shape_ptr));
	return (READ_OK);
}

int		get_tetrominoes_from_fd(int fd, t_list **tet_list)
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
		ERROR(return (READ_ERROR), "no tetrominoes found");
	else
		return (READ_COMPLETE);
}

#define EXIT ({ ft_putstr_fd("error\n", 2); return (0); })

int main(int ac, char **av)
{
	t_list *tet_list;
	
	tet_list = NULL;
	if ((get_tetrominoes_from_fd(open(av[1], O_RDONLY), &tet_list)) == READ_ERROR)
		EXIT ;
		
	
	(void)ac;
	return (0);
}
