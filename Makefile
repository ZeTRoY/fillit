NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_piece.c get_pieces.c backtracking_solution.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -L ./libft -lft -o $(NAME)

$(OBJS): $(SRCS)
	gcc -I libft -c $(SRCS)

clean:
	-rm $(OBJS)

fclean: clean
	-rm $(NAME)

re: fclean all
