NAME = philo
CC = cc
CFLAGS = -Wall Wextra -Werror
SRC = main.c parse.c init.c actions.c monitor.c utils.C
OBJ = $(SRC: .c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all