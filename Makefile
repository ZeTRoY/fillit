NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_piece.c get_pieces.c make_table.c hide.c hide2.c solve.c ft_putendl.c ft_puterr.c ft_putstr.c ft_strlen.c ft_bzero.c ft_endl.c shift.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
	gcc -c $(SRCS)

clean:
	-rm $(OBJS)

fclean: clean
	-rm $(NAME)

re: fclean all
