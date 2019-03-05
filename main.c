#include "lib/libft/libft.h"
#include "fillit.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

char**	parse_tetronimo(int fd)
{
	char	*buf[TETROMINO_FORMAT_N_BYTES];
	int		read_returned;
	char	**shape;
	int		idx;

	ft_bzero(buf, TETROMINO_FORMAT_N_BYTES);
	if ((read(fd, buf, TETROMINO_FORMAT_N_BYTES)) != TETROMINO_FORMAT_N_BYTES)
		ERROR(NULL, "read() failed");
	shape = malloc(sizeof(char) * TETROMINO_BOUNDING_SIZE * TETROMINO_BOUNDING_SIZE);
	idx = 0;
	while (idx < TETROMINO_FORMAT_N_BYTES)
	{
		if (NOT(IS_VALID_CHR(buf[idx])))
			ERROR(NULL, ft_strjoin("Encountered invalid char: ", ft_strndup(&buf[idx], 1)));
		if (buf[idx] == '\n')
			
		
	}
}


int main()
{
	struct s_tetromino *tetromino = malloc(sizeof(struct s_tetromino));
	tetromino->shape = [['#','.','.','.'],
						['#','.','.','.'],
						['#','.','.','.'],
						['#','.','.','.']];
	tetromino->x_pos = 0;
	tetromino->y_pos = 0;
	ft_putstr(CYAN);
	ft_putstr("HMM\n");
	ft_putstr(MAGENTA);
	ft_putstr("GORGEOUS\n");
	return (0);
}

