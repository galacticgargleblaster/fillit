/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:39:23 by marvin            #+#    #+#             */
/*   Updated: 2019/03/30 01:51:14 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

unsigned char	absolute_x(const t_guess *g, unsigned char i)
{
	return (g->coord.x + g->tet->shape[i].x);
}

unsigned char	absolute_y(const t_guess *g, unsigned char i)
{
	return (g->coord.y + g->tet->shape[i].y);
}