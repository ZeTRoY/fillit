# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroi <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/15 14:34:23 by aroi              #+#    #+#              #
#    Updated: 2018/04/15 14:34:32 by aroi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_piece.c get_pieces.c make_table.c hide.c hide2.c solve.c ft_putendl.c ft_puterr.c ft_putstr.c ft_strlen.c ft_bzero.c ft_endl.c shift.c free.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	gcc -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
