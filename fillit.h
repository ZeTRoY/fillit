/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:59:49 by ibarabas          #+#    #+#             */
/*   Updated: 2018/04/11 16:36:40 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define X 0
# define Y 1

# include <fcntl.h>

typedef struct			s_data_obj
{
	struct s_data_obj	*up;
	struct s_data_obj	*down;
	struct s_data_obj	*left;
	struct s_data_obj	*right;
	struct s_c_header	*column;
}						t_data_obj;

typedef struct			s_c_header
{
	struct s_c_header	*up;
	struct s_c_header	*down;
	struct s_c_header	*left;
	struct s_c_header	*right;
	struct s_c_header	*column;
	char				name;
	unsigned int		size;
}						t_c_header;

typedef struct			s_piece
{
	char 				points[4][2];
	struct s_piece		*next;
	struct s_piece		*prev;
}						t_piece;

int						get_next_piece(const int fd, char **dest);
t_piece					*get_pieces(int fd);
int						solve(t_piece *piece);

#endif
