/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 11:02:29 by aroi              #+#    #+#             */
/*   Updated: 2018/04/15 14:31:30 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	free_node(t_node *rootnode)
{
	t_node	*tmp;
	t_node	*node;

	node = rootnode->down;
	while (node != rootnode)
	{
		tmp = node;
		node->down->up = node->up;
		node->up->down = node->down;
		node = node->down;
		free(tmp);
	}
	free(node);
}

void	free_piece(t_piece *piece)
{
	free_node(piece->column);
	free(piece);
}
