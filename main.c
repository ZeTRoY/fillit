/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:59:22 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/06 13:24:54 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

#include <stdio.h> // Только для тестов, нужно будет удалить

int main(int ac, char **av)
{
	int fd;
	char *buf;

	if (ac != 2)
	{
		ft_putendl("usage: fillit source_file");
		exit(0);
	}
	fd = open(av[1], O_RDONLY);

	t_piece	*piece;
	t_piece *origin;
   
	if ((piece = get_pieces(fd)) == NULL)
		printf("%s\n", "error");
	origin = piece;

	int i = 1;

	// Вот для этих
	printf("\n");
	while (piece != NULL)
	{
		printf("%d%s:\n", i++, "-я фигура");
		int j = 0;
		while (j < 4)
		{
			printf("(%d, %d) ", piece->points[j][X], piece->points[j][Y]);
			j++;
		}
		printf("\n\n");
		piece = piece->next;
	}
	printf("%s%d\n\n", "Минимальный размер квадрата: ", solve(origin));
	return (0);
}
