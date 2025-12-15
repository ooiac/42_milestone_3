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
       src/executor/exec_ast_1.c \
       src/executor/exec_ast_2.c \
       src/executor/exec_ast_3.c \
       src/executor/resolve_path.c \
       src/executor/redir_utils.c \
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
       src/lexer/tokenize_utils_1.c \
       src/lexer/tokenize_utils_2.c \
       src/lexer/tokenize_utils_3.c \
       src/parser/ast_builder_1.c \
       src/parser/ast_builder_2.c \
       src/parser/ast_builder_3.c \
       src/parser/ast_builder_utils.c \
       src/parser/ast_utils.c \
       src/parser/ast_logical.c \
       src/parser/redir_utils.c \
       src/parser/syntax_check.c \
       src/expander/expand_string.c \
       src/expander/expand_string_utils.c \
       src/expander/expander.c \
       src/expander/expander_quotes.c \
       src/expander/expander_utils.c \
       src/expander/expander_variable.c \
       src/heredoc/heredoc.c \
       src/heredoc/heredoc_collect_1.c \
       src/heredoc/heredoc_collect_2.c \
       src/heredoc/heredoc_expand.c \
       src/heredoc/heredoc_utils.c

OBJS = $(SRCS:.c=.o)
TOTAL_SRCS := $(words $(SRCS))

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
BLUE = \033[0;34m
RESET = \033[0m
BOLD = \033[1m

define POLENTA_ART
$(YELLOW)
╔═══════════════════════════════════════════════════════════════════════╗
║                                                                       ║
║   ██████╗  ██████╗ ██╗     ███████╗███╗   ██╗████████╗ █████╗       	║
║   ██╔══██╗██╔═══██╗██║     ██╔════╝████╗  ██║╚══██╔══╝██╔══██╗      	║
║   ██████╔╝██║   ██║██║     █████╗  ██╔██╗ ██║   ██║   ███████║      	║
║   ██╔═══╝ ██║   ██║██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══██║      	║
║   ██║     ╚██████╔╝███████╗███████╗██║ ╚████║   ██║   ██║  ██║      	║
║   ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝      	║
║                                                                       ║
║         ███████╗██████╗ ██╗████████╗ █████╗                         	║
║         ██╔════╝██╔══██╗██║╚══██╔══╝██╔══██╗                        	║
║         █████╗  ██████╔╝██║   ██║   ███████║                        	║
║         ██╔══╝  ██╔══██╗██║   ██║   ██╔══██║                        	║
║         ██║     ██║  ██║██║   ██║   ██║  ██║                        	║
║         ╚═╝     ╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝                        	║
║                                                                       ║
║              $(CYAN)🍟  The crunchiest shell  🍟$(YELLOW)                     	║
║                                                                       ║
╚═══════════════════════════════════════════════════════════════════════╝
$(RESET)
endef
export POLENTA_ART

all: $(LIBFT) $(NAME)
	@clear
	@echo "$$POLENTA_ART"
	@echo "$(GREEN)Polenta Frita compiled successfully! $(RESET)\n"

$(LIBFT):
	@echo "$(CYAN)$(BOLD)🔧 Compiling libft...$(RESET)"
	@$(MAKE) -C libft --no-print-directory

COMPILED = 0
%.o: %.c
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@$(eval PERCENT=$(shell echo $$(($(COMPILED)*100/$(TOTAL_SRCS)))))
	@printf "\r$(YELLOW)$(BOLD)⚡ Compiling Polenta Frita... $(BLUE)[$(PERCENT)%%] $(GREEN)"
	@printf "%-50s" "[$<]"
	@printf "$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@printf "\n$(CYAN)$(BOLD)🔗 Linking files...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@$(MAKE) -C libft clean --no-print-directory
	@rm -f $(OBJS)
	@echo "$(YELLOW)🧹 Object files removed$(RESET)"

fclean: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(YELLOW)🗑️  Done complete cleaning$(RESET)"

re: fclean all

.PHONY: all clean fclean re
