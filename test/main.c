/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/12 00:55:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "../fillit.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include "../constructors.c"  // Include the .c file to get access to a static function.  Because "translation units" or something
#define COLORS
#include "../print.c"
#include "../solve.c"

#define GREEN_OK() (ft_putstr(GREEN), ft_putstr("OK"), ft_putstr(RESET))
#define RED_FAIL() (ft_putstr(RED), ft_putstr("FAIL"), ft_putstr(RESET))

#define ASSERT(cond) (\
	{\
		int assertion_failed = ((cond) == 0);\
		if (assertion_failed)\
		{\
			ft_putstr("condition: `");\
			ft_putstr(#cond);\
			ft_putstr("` is untrue. (");\
			ft_putstr(__FILE__);\
			ft_putstr(", line ");\
			ft_putstr(ft_itoa(__LINE__));\
			ft_putstr(") ");\
		}\
		assertion_failed;\
	}\
)\

static int g_err; 

#define DO_TEST(f) ( \
	{  \
		ft_putstr(#f); \
		ft_putstr("\t"); \
		int result = f();  \
		if (result == 0)  \
			GREEN_OK(); \
		else \
		{ \
			RED_FAIL(); \
			g_err++; \
		} \
		ft_putstr("\n"); \
	}) \

t_shape valid_i_shape = {
	{'#', '.', '.', '.'},
	{'#', '.', '.', '.'},
	{'#', '.', '.', '.'},
	{'#', '.', '.', '.'},
};

t_shape valid_o_shape = {
	{'.', '.', '.', '.'},
	{'.', '.', '#', '#'},
	{'.', '.', '#', '#'},
	{'.', '.', '.', '.'},
};

t_shape valid_l_shape = {
	{'#', '.', '.', '.'},
	{'#', '.', '.', '.'},
	{'#', '#', '.', '.'},
	{'.', '.', '.', '.'},
};

t_shape valid_j_shape = {
	{'.', '#', '#', '.'},
	{'.', '#', '.', '.'},
	{'.', '#', '.', '.'},
	{'.', '.', '.', '.'},
};

int	test_min_max_finding_with_i()
{
	t_tetromino tet = 
	{
		.shape = &valid_i_shape
	};

	init_tet_min_max(&tet);
	ASSERT(tet.x_min == 0);
	assert(tet.x_max == 0);
	assert(tet.y_min == 0);
	assert(tet.y_max == 3);
	return (0);
}

int	test_min_max_finding_with_o()
{
	t_tetromino tet = 
	{
		.shape = &valid_o_shape
	};

	init_tet_min_max(&tet);
	assert(tet.x_min == 2);
	assert(tet.x_max == 3);
	assert(tet.y_min == 1);
	assert(tet.y_max == 2);
	return (0);
}


int	test_that_non_overlapping_tetrominoes_dont_overlap_basic()
{
	t_tetromino *o = new_tetromino(&valid_o_shape);
	t_tetromino *i = new_tetromino(&valid_i_shape);

	return ASSERT(intersects_with(o, i) == 0);
}

int	test_that_non_overlapping_tetrominoes_dont_overlap()
{
	t_tetromino *o = new_tetromino(&valid_o_shape);
	t_tetromino *j = new_tetromino(&valid_j_shape);

	return ASSERT(intersects_with(o, j) == 0);
}

int	test_that_overlapping_tetrominoes_do_overlap()
{
	t_tetromino *o = new_tetromino(&valid_o_shape);
	t_tetromino *j = new_tetromino(&valid_j_shape);
	j->coord.x = 1;

	return ASSERT(intersects_with(o, j));

}

int	main()
{

	DO_TEST(test_min_max_finding_with_i);
	DO_TEST(test_min_max_finding_with_o);
	DO_TEST(test_that_non_overlapping_tetrominoes_dont_overlap_basic);
	DO_TEST(test_that_non_overlapping_tetrominoes_dont_overlap);
	DO_TEST(test_that_overlapping_tetrominoes_do_overlap);

	if (g_err == 0)
	{
		ft_putstr(GREEN);
		ft_putstr("ALL TESTS OK\n");
		ft_putstr(RESET);
	}
	else
	{
		ft_putstr(RED);
		ft_putstr(ft_strjoin(ft_itoa(g_err), " TESTS FAILED\n"));
		ft_putstr(RESET);
	}
	return (0);
}