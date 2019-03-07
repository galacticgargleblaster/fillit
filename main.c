/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/07 15:38:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define EXIT ({ ft_putstr_fd("error\n", 2); return (0); })

int	main(int ac, char **av)
{
	t_list	*tet_list;
	
	tet_list = NULL;
	if ((read_tetrominoes_from_fd(open(av[1], O_RDONLY), &tet_list)) == READ_ERROR)
		EXIT ;
	
	(void)ac;
	return (0);
}
