/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 14:48:40 by student          ###   ########.fr       */
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
	t_doubly_linked_list *tet_list;
	
	tet_list = new_doubly_linked_list();
	if ((read_tetrominoes_from_fd(open(av[1], O_RDONLY), tet_list)) == READ_ERROR)
		EXIT ;
	print_tetrominoes(tet_list);
	naive_solve(tet_list);
	(void)ac;
	return (0);
}
