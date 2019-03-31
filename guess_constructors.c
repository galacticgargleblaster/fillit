/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess_constructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 21:18:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

t_guess				*new_guess(unsigned char x, unsigned char y, t_tetromino *t)
{
	t_guess	*guess;

	guess = malloc(sizeof(t_guess));
	if (guess == NULL)
		return (NULL);
	guess->tet = t;
	guess->coord.x = x;
	guess->coord.y = y;
	return (guess);
}

void				*copy_guess(void *g_ptr)
{
	t_guess	*guess;

	guess = (t_guess *)g_ptr;
	return (new_guess(guess->coord.x, guess->coord.y, guess->tet));
}
