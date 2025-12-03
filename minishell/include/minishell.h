/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:44:30 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/03 13:10:45 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "token.h"
# include "ast.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "heredoc.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

/* env */
t_env	*env_from_envp(char **envp);
void	free_env(t_env *env);
char	*env_get(t_env *env, const char *key);
char	**env_to_envp(t_env *env);
void	free_envp(char **envp);

/* exec */
char	*resolve_executable(const char *cmd, t_env *env);
int		run_single_command(char **av, t_env *env);
int		run_pipeline(char ***cmds, t_env *env);
int		exec_ast(t_ast *ast, t_env **env);
int		exec_pipeline_recursive(t_ast *ast, t_env *env, int input_fd);
int		apply_redirections(t_redir *redirs);
int		exec_simple_command(t_ast *ast, t_env **env);

/* pipeline helpers */
typedef struct s_pipe_ctx
{
	int		**pipes;
	int		i;
	int		n_cmds;
	t_env	*env;
}	t_pipe_ctx;

int		**create_pipes(int n);
void	close_all_pipes(int **pipes, int n);
void	exec_in_pipeline(char **cmd, t_pipe_ctx *ctx);
int		wait_all(pid_t *pids, int n);

/* builtins */
int		is_builtin(const char *cmd);
int		exec_builtin(char **args, t_env **env);
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_cd(char **args, t_env **env);
int		builtin_export(char **args, t_env **env);
int		builtin_unset(char **args, t_env **env);
int		builtin_exit(char **args);

/* main loop */
void	start_shell(t_env *env);

/* signals */
extern volatile sig_atomic_t	g_signal_received;
void	setup_signals_prompt(void);
void	setup_signals_exec(void);
void	setup_signals_heredoc(void);
void	setup_signals_default(void);

#endif