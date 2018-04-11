/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_piece.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:15:02 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/06 10:11:44 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Выделяет и обнуляет 22 байта памяти
**	Читает 21 символ из fd в буфер temp
**	Проверяет, состоит ли полученная строка из четырех строк
**	по четыре символа, и нет ли в ней лишних символов
**	Если все плохо - освобождает память и возвращает -1
**	Иначе присваивает строку указателю dest и возвращает то, что вернул read()
**	Каждое использование get_next_piece() возвращает следующую фигуру
*/

static int	is_valid(char *temp, int i)
{
	if ((i + 1) % 5 < 4 && temp[i + 1] == '#')
		return (1);
	if ((i + 1) % 5 > 1 && temp[i - 1] == '#')
		return (1);
	if ((i + 1) / 5 > 0 && temp[i - 5] == '#')
		return (1);
	if ((i + 1) / 5 < 4 && temp[i + 5] == '#')
		return (1);
	return (0);
}

static int	errcheck(char *temp)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if ((i + 1) % 5 == 0)
		{
			if (temp[i] != '\n')
				return (-1);
		}
		else if (temp[i] != '.' && temp[i] != '#')
			return (-1);
		else if (temp[i] == '#' && !is_valid(temp, i))
			return (-1);
		i++;
	}
	if (temp[i] != '\n' && temp[i] != '\0')
		return (-1);
	return (1);
}

int			get_next_piece(const int fd, char **dest)
{
	int		rvalue;
	char	*temp;

	if (!dest)
		return (-1);
	if (!(temp = (char *)malloc(22)))
		return (-1);
	ft_bzero(temp, 22);
	if ((rvalue = read(fd, temp, 21)) < 1)
		return (rvalue);
	if (errcheck(temp) == -1)
	{
		free(temp);
		return (-1);
	}
	*dest = temp;
	return (rvalue);
}
