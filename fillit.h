/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:59:49 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/15 12:35:42 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define X 0
# define Y 1

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_piece
{
	char			points[4][2];
	struct s_piece	*prev;
	struct s_piece	*next;
	struct s_node	*column;
	char			id;
}					t_piece;

typedef struct		s_node
{
	char			pos[2];
	struct s_node	*up;
	struct s_node	*down;
	struct s_piece	*head;
}					t_node;

typedef struct		s_hidden
{
	struct s_node	*node;
	struct s_hidden	*next;
}					t_hidden;

typedef struct		s_sol
{
	struct s_piece	*piece;
	struct s_node	*position;
	struct s_sol	*next;
}					t_sol;

/*
**	Функции из библиотеки libft
*/

int					ft_strlen(const char *s);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_puterr(char const *s);
void				ft_endl(void);
void				ft_bzero(void *s, size_t n);

/*
**	Функции расположены в порядке использования
*/

/*
**	get_next_piece.c
**	Читает 21 символ из fd в *dest,
**	получая следующую фигуру в виде строки.
*/

int					get_next_piece(const int fd, char **dest);

/*
**	get_pieces.c
**	Обрабатывает полученную строку
**	Возвращает список структур t_piece,
**	содержащих координаты четырех точек,
**	занимаемых фигурой
*/

t_piece				*get_pieces(int fd);
void				shift(t_piece *piece);

char				get_minimum_square(t_piece *root);

/*
**	make_table.c
**	Для каждой фигуры создаёт колонку
**	с её возможными расположениями
**	Получается замкнутый двухмерный список
*/

int					make_table(t_piece *root, int size);

t_hidden			*hide(t_piece *root, t_node *placement);
void				unhide(t_hidden *hidden, t_piece *col);

void				node_set_hidden(t_node *node, int hidden);
void				col_set_hidden(t_piece *piece, int hidden);

/*
**	solve.c
**	Использует метод dancing links,
**	Чтобы найти решение.
*/

int					solve(t_piece *root, t_sol *sols);

void				free_node(t_node *rootnode);
void				free_piece(t_piece *root);

#endif
