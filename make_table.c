/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:25:30 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/15 13:19:52 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Нужно для fill_col()
**	Проверяет, можно ли разместить фигуру здесь,
**	и добавляет элемент к столбцу, если да
*/

static int	add(t_piece *piece, t_node *node, int x, int y)
{
	node = piece->column;
	while (node->down != piece->column)
		node = node->down;
	if (!(node->down = (t_node *)malloc(sizeof(t_node))))
		return (-1);
	node->down->pos[X] = x;
	node->down->pos[Y] = y;
	node->down->head = piece;
	node->down->up = node;
	node->down->down = piece->column;
	return (0);
}

static int	validate_and_add(t_piece *piece, int x, int y, int size)
{
	t_node	*node;
	int		i;
	int		valid;

	i = 0;
	valid = 1;
	while (i < 4)
	{
		if (piece->points[i][X] + x >= size
				|| piece->points[i][Y] + y >= size)
		{
			valid = 0;
			break ;
		}
		i++;
	}
	if (valid)
	{
		if (add(piece, node, x, y) == -1)
			return (-1);
	}
	return (0);
}

/*
**	Нужно для create_col()
**	Заполняет колонку
*/

static void	fill_col(t_piece *piece, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			validate_and_add(piece, x, y, size);
			x++;
		}
		y++;
	}
}

/*
**	Принимает структуру t_piece и размер квадрата
**	Создает замкнутый столбец с возможными положениями фигуры
**	У корня столбца координата X равна -1
*/

static int	create_col(t_piece *piece, int size)
{
	t_node	*root;
	t_node	*node;

	if (!(root = (t_node *)malloc(sizeof(t_node))))
		return (-1);
	root->head = piece;
	piece->column = root;
	root->pos[X] = -1;
	root->down = root;
	fill_col(piece, size);
	return (0);
}

/*
**	Создает таблицу, используя create_col()
**	на каждой фигуре
*/

int			make_table(t_piece *root, int size)
{
	t_piece	*piece;

	piece = root;
	while (piece->next != root)
	{
		piece = piece->next;
		create_col(piece, size);
	}
	return (0);
}
