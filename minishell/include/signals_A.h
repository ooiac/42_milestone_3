/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:minishell/include/minishell.h
/*   Created: 2025/11/10 17:44:30 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 15:21:53 by caida-si         ###   ########.fr       */
=======
/*   Created: 2025/11/20 20:47:31 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 21:45:58 by fluca            ###   ########.fr       */
>>>>>>> origin/fluca2:minishell/include/signals_A.h
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal_received;

void	setup_signals_prompt(void);
void	setup_signals_exec(void);
void	setup_signals_heredoc(void);
void	setup_signals_default(void);

<<<<<<< HEAD:minishell/include/minishell.h
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

/* pipeline helpers */
int		**create_pipes(int n);
void	close_all_pipes(int **pipes, int n);
void	exec_in_pipeline(char **cmd, int **pipes, int i, int n_cmds,
						t_env *env);
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

#endif
=======
#endif
>>>>>>> origin/fluca2:minishell/include/signals_A.h
