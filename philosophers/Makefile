NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
LDFLAGS = -pthread
SRC = main.c parse.c init.c actions.c monitor.c utils.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all