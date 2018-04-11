/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pieces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 10:26:39 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/06 12:59:58 by ibarabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
**	Часть кода из функции convert(), проверяет текущую строку
*/

int		i_love_norminette(int *found, int i, t_piece *piece, char *str)
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
		rvalue = i_love_norminette(&found, i, piece, str);
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
**	Преобразует координаты так, чтобы фигура оказалась в левом верхнем углу
**	Например, вертикальная линия с координатами:
**	(0, 3) (1, 3) (2, 3) (3, 3)
**	Превращается в:
**	(0, 0) (1, 0) (2, 0) (3, 0)
*/

void	shift(t_piece *piece)
{
	int	i;
	int can_shift;

	while (can_shift)
	{
		can_shift = 1;
		i = -1;
		while (++i < 4)
			if (piece->points[i][X] == 0)
				can_shift = 0;
		i = -1;
		if (can_shift)
			while (++i < 4)
				piece->points[i][X] -= 1;
		can_shift = 1;
		i = -1;
		while (++i < 4)
			if (piece->points[i][Y] == 0)
				can_shift = 0;
		i = -1;
		if (can_shift)
			while (++i < 4)
				piece->points[i][Y] -= 1;
	}
}

/*
** Часть кода из функции get_pieces()
*/

int		i_love_norminette_part_2(t_piece **pieces, char *str)
{
	t_piece	*temp;

	temp = *pieces;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		if ((temp->next = convert(str)) == NULL)
			return (-1);
		temp->next->next = NULL;
		shift(temp);
	}
	else
	{
		if ((*pieces = convert(str)) == NULL)
			return (-1);
		(*pieces)->next = NULL;
		shift(*pieces);
	}
	free(str);
	return (1);
}

/*
**	Cобирает все функции воедино
**	Принимает единственный аргумент - файловый дескриптор
**	Возвращает список структур с координатами фигур
*/

t_piece	*get_pieces(int fd)
{
	int		n;
	int		rvalue;
	char	*str;
	char	endl;
	t_piece	*pieces;

	n = 0;
	pieces = NULL;
	while ((rvalue = get_next_piece(fd, &str)) != 0 && n < 26)
	{
		if (rvalue == -1)
			return (NULL);
		endl = str[20];
		rvalue = i_love_norminette_part_2(&pieces, str);
		if (rvalue < 0)
			return (NULL);
		n++;
	}
	if (endl != '\0')
		return (NULL);
	return (pieces);
}
