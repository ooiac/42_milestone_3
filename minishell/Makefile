NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./libft

LIBFT = libft/libft.a
LDFLAGS = -L./libft -lft -lreadline

SRCS = main.c \
       src/env/env.c \
       src/env/env_to_envp.c \
       src/executor/exec.c \
       src/executor/exec_ast.c \
       src/executor/resolve_path.c \
       src/executor/pipeline.c \
       src/executor/pipeline_utils.c \
       src/shell/shell.c \
       src/builtins/builtin_utils.c \
       src/builtins/builtin_echo.c \
       src/builtins/builtin_pwd.c \
       src/builtins/builtin_env.c \
       src/builtins/builtin_cd.c \
       src/builtins/builtin_export.c \
       src/builtins/builtin_unset.c \
       src/builtins/builtin_exit.c \
       src/signals/signals_prompt.c \
       src/signals/signals_exec.c \
       src/signals/signals_heredoc.c \
       src/signals/signals_utils.c \
       src/lexer/lexer.c \
       src/lexer/token_list.c \
       src/lexer/tokenize_utils.c \
       src/parser/ast_builder.c \
       src/parser/ast_utils.c \
       src/parser/redir_utils.c \
       src/parser/syntax_check.c \
       src/expander/expand_string.c \
       src/expander/expander.c \
       src/expander/expander_quotes.c \
       src/expander/expander_utils.c \
       src/expander/expander_variable.c \
       src/heredoc/heredoc.c \
       src/heredoc/heredoc_collect.c \
       src/heredoc/heredoc_expand.c \
       src/heredoc/heredoc_utils.c

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
