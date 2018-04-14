/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_piece.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 12:15:02 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/14 14:40:34 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Обходит глупые ограничения нормы
*/

static void	set(int *c, int *dest, int value)
{
	(*c)++;
	(*dest) = value;
}

/*
**	Вызывается функцией is_valid(), если квадратик касается только одного
**	другого. Убеждается, что квадратик, которого касается квадратик,
**	касается ещё одного квадратика
*/

static int	is_really_valid(char *temp, int i, int root)
{
	if ((i + 1) % 5 < 4 && temp[i + 1] == '#' && i + 1 != root)
		return (1);
	if ((i + 1) % 5 > 1 && temp[i - 1] == '#' && i - 1 != root)
		return (1);
	if ((i + 1) / 5 > 0 && temp[i - 5] == '#' && i - 5 != root)
		return (1);
	if ((i + 1) / 5 < 4 && temp[i + 5] == '#' && i + 5 != root)
		return (1);
	return (0);
}

/*
**	Убеждается, что возле каждого квадратика есть еще хотя бы один квадратик
*/

static int	is_valid(char *temp, int i)
{
	int	connections;
	int	last_found;

	connections = 0;
	if ((i + 1) % 5 < 4 && temp[i + 1] == '#')
		set(&connections, &last_found, i + 1);
	if ((i + 1) % 5 > 1 && temp[i - 1] == '#')
		set(&connections, &last_found, i - 1);
	if ((i + 1) / 5 > 0 && temp[i - 5] == '#')
		set(&connections, &last_found, i - 5);
	if ((i + 1) / 5 < 4 && temp[i + 5] == '#')
		set(&connections, &last_found, i + 5);
	if (connections > 1)
		return (1);
	else if (connections == 1)
		if (is_really_valid(temp, last_found, i))
			return (1);
	return (0);
}

/*
**	Проверяет на ошибки в файле
*/

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

/*
**	Выделяет и обнуляет 22 байта памяти
**	Читает 21 символ из fd в буфер temp
**	Проверяет, состоит ли полученная строка из четырех строк
**	по четыре символа, и нет ли в ней лишних символов
**	Если все плохо - освобождает память и возвращает -1
**	Иначе присваивает строку указателю dest и возвращает то, что вернул read()
**	Каждое использование get_next_piece() возвращает следующую фигуру
*/

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
