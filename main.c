/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/14 10:33:38 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define EXIT ({ ft_putstr_fd("error\n", 2); return (0); })


int	main(int ac, char **av)
{
	t_list	*tet_list;
	
	tet_list = NULL;
	if ((read_tetrominoes_from_fd(open(av[1], O_RDONLY), &tet_list)) == READ_ERROR)
		EXIT ;
	
	naive_solve(tet_list);
	(void)ac;
	return (0);
}
