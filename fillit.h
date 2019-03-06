
#ifdef DEBUG
#define PUTERR(msg) (ft_putstr_fd(ft_strjoin(msg, "\n"), 2))
#else
#define PUTERR(msg)
#endif

#define TETROMINO_BOUNDING_SIZE 4

struct		s_tetromino
{
	char	shape[4][4];
	size_t	x_pos;
	size_t	y_pos;
	
};


