/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pieces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 10:26:39 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/15 13:26:15 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Нужно для функции convert()
**	Записывает клетки, занимаемые фигурой
*/

int		get_points(int *found, int i, t_piece *piece, char *str)
{
	int			j;

	j = 0;
	while (j < 4)
	{
		if (str[i * 5 + j] == '#')
		{
			if (*found >= 4)
				return (-42);
			piece->points[*found][Y] = i;
			piece->points[*found][X] = j;
			(*found)++;
		}
		j++;
	}
	return (*found);
}

/*
**	Принимает строку, которую вернула функция get_next_piece()
**	Возвращает указатель на структуру t_piece
**	с координатами четырех ячеек, занимаемых фигурой
**	Если что-то пошло не так, или если символов '#' не четыре,
**	то возвращает NULL
*/

t_piece	*convert(char *str)
{
	int		found;
	int		i;
	int		rvalue;
	t_piece *piece;

	found = 0;
	if (!(piece = (t_piece *)malloc(sizeof(t_piece))))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		rvalue = get_points(&found, i, piece, str);
		if (rvalue == -42)
		{
			free(piece);
			return (NULL);
		}
		i++;
	}
	if (rvalue != 4)
	{
		free(piece);
		return (NULL);
	}
	return (piece);
}

/*
**	Нужно для get_pieces()
**	Добавляет фигуру, содержащуюся в str, к списку *pieces
**	Делает список замкнутым
*/

int		add_piece(t_piece *root, t_piece **pieces, char *str, int n)
{
	while ((*pieces)->next != root)
		(*pieces) = (*pieces)->next;
	if (((*pieces)->next = convert(str)) == NULL)
		return (-1);
	(*pieces)->next->next = root;
	root->prev = (*pieces)->next;
	(*pieces)->next->prev = *pieces;
	shift((*pieces)->next);
	(*pieces)->next->id = 'A' + n;
	free(str);
	return (1);
}

/*
**	Применяет add_piece() ко всем фигурам из fd
*/

int		add_everything(int fd, int n, t_piece *pieces, t_piece *root)
{
	int		rvalue;
	char	endl;
	char	*str;
	int		pass;

	pass = 0;
	while ((rvalue = get_next_piece(fd, &str)) != 0 && n < 26)
	{
		if (!pass)
			pass = 1;
		if (rvalue == -1)
			return (-1);
		endl = str[20];
		if (add_piece(root, &pieces, str, n) < 0)
			return (-1);
		n++;
	}
	if (rvalue == 0 && !pass)
		return (-1);
	if (endl != '\0')
		return (-1);
	free(str);
	return (0);
}

/*
**	Cобирает все функции воедино
**	Принимает единственный аргумент - файловый дескриптор
**	Возвращает замкнутый список структур с координатами фигур
*/

t_piece	*get_pieces(int fd)
{
	int		n;
	t_piece	*pieces;
	t_piece	*root;

	n = 0;
	if (!(pieces = (t_piece *)malloc(sizeof(t_piece))))
		return (NULL);
	pieces->next = pieces;
	root = pieces;
	if (add_everything(fd, n, pieces, root) < 0)
		return (NULL);
	return (root);
}
