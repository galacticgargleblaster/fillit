/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 01:24:29 by student          ###   ########.fr       */
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
	t_solver_context	*context;
	
	tet_list = new_doubly_linked_list();
	if (ERROR == (read_tetrominoes_from_fd(open(av[1], O_RDONLY), tet_list)))
		EXIT ;
	print_tetrominoes(tet_list);
	context = naive_solve(tet_list);
	if (context)
		print_context(context);
	else
		PUT_ERR("No solution");
	(void)ac;
	return (0);
}
