/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:21 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:43:57 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	translate_status(int status)
{
	if (WIFIEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static void	run_child(char **av, t_env *env, char *path)
{
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = env_to_envp(env);
	if (!envp)
		exit(1);
	execve(path, av, envp);
	perror(av[0]);
	free_envp(envp);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static void	ft_err_msg(const char *cmd, const char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

int	run_single_command(char **av, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!av || !av[0])
		return (0);
	path = resolve_executable(av[0], env);
	if (!path)
	{
		ft_err_msg(av[0], "command not found");
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		return (1);
	}
	if (pid == 0)
		run_child(av, env, path);
	free(path);
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	return (translate_status(status));
}

int	run_pipeline(char ***cmds, t_env *env)
{
	int		**pipes;
	pid_t	*pids;
	int		n_cmds;
	int		i;

	n_cmds = 0;
	while (cmds[n_cmds])
		n_cmds++;
	pipes = create_pipes(n_cmds - 1);
	pids = malloc(sizeof(pid_t) * n_cmds);
	i = 0;
	while (i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			exec_in_pipeline(cmds[i], pipes, i, n_cmds, env);
		i++;
	}
	close_all_pipes(pipes, n_cmds - 1);
	return (wait_all(pids, n_cmds));
}
