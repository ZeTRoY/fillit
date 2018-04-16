/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 12:50:46 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/16 15:22:43 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
**	Все фигуры состоят из четырех ячеек.
**	То есть, квадрат со стороной N может содержать,
**	в лучшем случае, (N^2)/4 фигур.
**	Это и использует следующая функция.
*/

char		get_minimum_square(t_piece *root)
{
	t_piece	*piece;
	char	piece_count;
	char	size;

	piece = root->next;
	piece_count = 0;
	while (piece != root)
	{
		piece_count++;
		piece = piece->next;
	}
	size = 0;
	while (size * size / 4 < piece_count)
		size++;
	return (size);
}

int			there_is_hope(t_piece *root)
{
	t_piece *col;

	col = root->next;
	while (col != root)
	{
		if (col->column->down == col->column)
			return (0);
		col = col->next;
	}
	return (1);
}

void		new_new_sol(t_sol **new_sol, t_piece *col, t_node *row)
{
	(*new_sol)->next->piece = col;
	(*new_sol)->next->position = row;
	(*new_sol)->next->next = NULL;
}

int			loop(t_piece *root, t_sol *sols, t_piece **col, t_node *row)
{
	t_hidden	*hidden;
	t_sol		*new_sol;

	hidden = NULL;
	row = (*col)->column->down;
	while (row != (*col)->column)
	{
		hidden = hide(root, row);
		new_sol = sols;
		while (new_sol->next != NULL)
			new_sol = new_sol->next;
		if (!(new_sol->next = (t_sol *)malloc(sizeof(t_sol))))
			return (-1);
		new_new_sol(&new_sol, *col, row);
		if (solve(root, sols) == 42)
		{
			unhide(hidden, (*col));
			return (42);
		}
		free(new_sol->next);
		new_sol->next = NULL;
		unhide(hidden, (*col));
		row = row->down;
	}
	return (0);
}

/*
**	Находит решение методом танцующих бубнов
*/

int			solve(t_piece *root, t_sol *sols)
{
	t_piece		*col;
	t_node		*row;
	int			rvalue;

	if (root->next == root)
		return (42);
	col = root->next;
	if (there_is_hope(root))
	{
		rvalue = loop(root, sols, &col, row);
		if (rvalue == 42)
			return (42);
		else if (rvalue == -1)
			return (-1);
	}
	return (0);
}
