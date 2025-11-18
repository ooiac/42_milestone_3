NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./libft

LIBFT = libft/libft.a
LDFLAGS = -L./libft -lft -lreadline

SRCS = src/main.c \
       src/env/env.c \
       src/env/env_to_envp.c \
       src/executor/exec.c \
       src/executor/resolve_path.c \
       src/executor/pipeline.c \
       src/executor/pipeline_utils.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
