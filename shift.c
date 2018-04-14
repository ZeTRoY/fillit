/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:26:10 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/14 14:52:20 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	shift_x(t_piece *piece)
{
	int i;
	int can_shift;

	can_shift = 1;
	while (can_shift)
	{
		can_shift = 1;
		i = -1;
		while (++i < 4)
			if (piece->points[i][X] == 0)
				can_shift = 0;
		i = -1;
		if (can_shift)
			while (++i < 4)
				piece->points[i][X] -= 1;
	}
}

void	shift_y(t_piece *piece)
{
	int i;
	int can_shift;

	can_shift = 1;
	while (can_shift)
	{
		can_shift = 1;
		i = -1;
		while (++i < 4)
			if (piece->points[i][Y] == 0)
				can_shift = 0;
		i = -1;
		if (can_shift)
			while (++i < 4)
				piece->points[i][Y] -= 1;
	}
}

void	shift(t_piece *piece)
{
	shift_x(piece);
	shift_y(piece);
}
