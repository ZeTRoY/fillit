/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:59:05 by aroi              #+#    #+#             */
/*   Updated: 2018/04/14 16:21:48 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		hide_n_seek(t_node *node, t_hidden **hidden, char pos[2],
		char pos2[4][2])
{
	int			j;
	t_hidden	*hidden_new;

	j = -1;
	while (++j < 4)
	{
		if (pos[X] == pos2[j][X] &&
				pos[Y] == pos2[j][Y])
		{
			hidden_new = (t_hidden *)malloc(sizeof(t_hidden));
			hidden_new->node = node;
			hidden_new->next = *hidden;
			*hidden = hidden_new;
			node_set_hidden(node, 1);
		}
	}
}

void		victory(t_piece *root, t_hidden **hidden, char pos[4][2])
{
	t_piece	*col;
	t_node	*node;
	int		i;
	char	pos2[4][2];

	col = root->next;
	while (col != root)
	{
		node = col->column->down;
		while (node->pos[X] != -1)
		{
			i = -1;
			while (++i < 4)
			{
				pos2[i][X] = node->pos[X] + node->head->points[i][X];
				pos2[i][Y] = node->pos[Y] + node->head->points[i][Y];
			}
			i = -1;
			while (++i < 4)
				hide_n_seek(node, hidden, pos[i], pos2);
			node = node->down;
		}
		col = col->next;
	}
}

/*
**	Принимает начало таблицы и выбранную клетку
**	Скрывает данную колонку, и
**	во всей таблице скрывает клетки,
**	где более нельзя поставить фигуру.
**	Возвращает список всего скрытого,
**	чтобы потом вернуть на место.
*/

t_hidden	*hide(t_piece *root, t_node *to_hide)
{
	t_piece		*col;
	t_hidden	*hidden;
	char		pos[4][2];
	int			i;

	hidden = NULL;
	col = to_hide->head;
	col_set_hidden(col, 1);
	i = -1;
	while (++i < 4)
	{
		pos[i][X] = to_hide->pos[X] + col->points[i][X];
		pos[i][Y] = to_hide->pos[Y] + col->points[i][Y];
	}
	victory(root, &hidden, pos);
	return (hidden);
}
