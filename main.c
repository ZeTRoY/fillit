/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:59:22 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/17 13:11:03 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
**	Подготавливает строку для печати
*/

void	prepare_for_printing(t_sol *solution, int size, char *board)
{
	int		i;
	char	x;
	char	y;
	t_sol	*tmp;

	free(solution->piece->prev);
	while (solution)
	{
		i = -1;
		while (++i < 4)
		{
			x = solution->piece->points[i][X];
			x += solution->position->pos[X];
			y = solution->piece->points[i][Y];
			y += solution->position->pos[Y];
			board[x * size + y] = solution->piece->id;
		}
		tmp = solution;
		solution = solution->next;
		free_piece(tmp->piece);
		free(tmp);
	}
}

void	print_solution(t_sol *solution, int size)
{
	char	board[size * size + 1];
	char	x;
	char	y;
	int		i;

	i = 0;
	while (i < size * size)
		board[i++] = '.';
	prepare_for_printing(solution, size, board);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			write(1, &board[x * size + y], 1);
			x++;
		}
		ft_endl();
		y++;
	}
}

void	clear_table(t_piece *root)
{
	t_piece	*col;
	t_node	*node;
	t_node	*temp;

	col = root->next;
	while (col != root)
	{
		if (col->column != NULL)
		{
			node = col->column;
			while ((temp = node->down) != node)
			{
				temp->down->up = temp->up;
				temp->up->down = temp->down;
				free(temp);
			}
			free(node);
		}
		col->column = NULL;
		col = col->next;
	}
}

void	main_solve(t_piece *root, int fd)
{
	t_sol	*sols;
	char	size;

	size = get_minimum_square(root) - 1;
	while (size++)
	{
		clear_table(root);
		make_table(root, size);
		if (!(sols = (t_sol *)malloc(sizeof(t_sol))))
			ft_puterr("error");
		sols->next = NULL;
		if (solve(root, sols) == 42)
		{
			print_solution(sols->next, size);
			free(sols);
			sols = NULL;
			close(fd);
			exit(0);
		}
		free(sols);
		sols = NULL;
	}
}

int		main(int ac, char **av)
{
	int		fd;
	char	*buf;
	t_piece	*root;

	if (ac != 2)
		ft_puterr("usage: fillit source_file");
	fd = open(av[1], O_RDONLY);
	if ((root = get_pieces(fd)) == NULL)
		ft_puterr("error");
	main_solve(root, fd);
	return (0);
}
