/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 07:14:18 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/14 15:42:13 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  Принимает 0 или 1
**  Скрывает или возвращает на место столбец
*/

void	col_set_hidden(t_piece *piece, int hidden)
{
	if (hidden == 1)
	{
		piece->prev->next = piece->next;
		piece->next->prev = piece->prev;
	}
	else
	{
		piece->prev->next = piece;
		piece->next->prev = piece;
	}
}

/*
**  То же самое, но с элементом столбца
*/

void	node_set_hidden(t_node *node, int hidden)
{
	if (hidden == 1)
	{
		node->down->up = node->up;
		node->up->down = node->down;
	}
	else
	{
		node->down->up = node;
		node->up->down = node;
	}
}

/*
**	Возвращает на место то, что было спрятано функцией hide.
*/

void	unhide(t_hidden *hidden, t_piece *col)
{
	t_hidden	*temp;

	col->next->prev = col;
	col->prev->next = col;
	while (hidden != NULL)
	{
		hidden->node->down->up = hidden->node;
		hidden->node->up->down = hidden->node;
		temp = hidden;
		hidden = hidden->next;
		free(temp);
	}
}
