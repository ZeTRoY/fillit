/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking_solution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 12:50:46 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/06 18:44:27 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
**	Все фигуры состоят из четырех ячеек.
**	То есть, квадрат со стороной N может содержать,
**	в лучшем случае, (N^2)/4 фигур.
**	Это и использует следующая функция.
*/

static char	get_minimum_square(t_piece *piece)
{
	char	piece_count;
	char	size;

	piece_count = 0;
	while (piece != NULL)
	{
		piece_count++;
		piece = piece->next;
	}
	size = 0;
	while (size * size / 4 < piece_count)
		size++;
	return (size);	
}

int		attempt(char	size)
{
	char	map[size][size];

	
}

/*
**	Вызывает рекурсивную функцию attempt,
**	используя размер квадрата size.
**	Если attempt возвращает 0,
**	то решение не найдено,
**	и делается следующая попытка
**	с увеличенным размером квадрата
*/

int		solve(t_piece *piece)
{
	char	size;
	char	found;

	size = get_minimum_square(piece);
	found = 0;
	return ((int)size);
}
