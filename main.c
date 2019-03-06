#include "lib/libft/libft.h"
#include "fillit.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
**	A tetronimo represented in fillit format consists of 16 chars + 4 newlines + 1 newline
*/
#define TETROMINO_FORMAT_N_BYTES 21

#define ERROR(ret, msg)({ PUTERR(msg); return (ret); })
#define Y_RAW(idx) (idx / (TETROMINO_BOUNDING_SIZE + 1))
#define X_RAW(idx) (idx % (TETROMINO_BOUNDING_SIZE + 1))
#define Y(idx) (MIN(Y_RAW(idx), TETROMINO_BOUNDING_SIZE - 1))
#define X(idx) (MIN(X_RAW(idx), TETROMINO_BOUNDING_SIZE - 1))
#define IS_VALID_CHR(c) (ft_strchr(".#\n", c ))

/*
**	Allocates and initializes memory to store the shape of a tetromino
*/
char	**new_shape()
{
	char	**shape;
	size_t	row;

	if ((shape = malloc(sizeof(char*) * TETROMINO_BOUNDING_SIZE)) == NULL)
		ERROR(NULL, "malloc failed");
	row = 0;
	while (row < TETROMINO_BOUNDING_SIZE)
	{
		if ((shape[row] = malloc(sizeof(char) * TETROMINO_BOUNDING_SIZE)) == NULL)
			ERROR(NULL, "malloc failed");
		ft_bzero(shape[row], TETROMINO_BOUNDING_SIZE);
		row++;
	}	
	return (shape);
}

/*
**	Transforms a string containing what may be a tetromino into a 4x4 char array
**	Returns the char array, or
**	Returns NULL if an error occurs
*/
char	**parse_tetromino(char *buf)
{
	char	**shape;
	int		idx;

	idx = 0;
	if ((shape = new_shape()) == NULL)
		ERROR(NULL, "can't get new shape");
	while (idx < TETROMINO_FORMAT_N_BYTES - 1)
	{
		if (NOT(IS_VALID_CHR(buf[idx])))
			ERROR(NULL, ft_strjoin("Encountered invalid char: ", ft_strndup(&buf[idx], 1)));
		if (idx % 5 == 0)
		{
			if (buf[idx] != '\n')
				ERROR(NULL, "newline found in wrong position");	
		}
		else
		{
			if (buf[idx] == '\n')
				ERROR(NULL, "newline found in wrong position");	
			shape[Y(idx)][X(idx)] = buf[idx];
		}
		idx++;
	}
	if (buf[idx] != '\n')
		ERROR(NULL, "trailing newline is missing");
	return (shape);
}

char	**get_next_tetromino_from_fd(int fd)
{
	char	*buf[TETROMINO_FORMAT_N_BYTES];

	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	if ((read(fd, buf, TETROMINO_FORMAT_N_BYTES)) != TETROMINO_FORMAT_N_BYTES)
		ERROR(NULL, "read() failed");
	return (parse_tetromino(buf[0]));
}


int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	char **tet = get_next_tetromino_from_fd(fd);

	(void)ac;
	(void)tet;
	return (0);
}

