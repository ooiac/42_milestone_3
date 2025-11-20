/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:24 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:38:24 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	setup_pipe_fds(int **pipes, int i, int n_cmds)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < n_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	exec_in_pipeline(char **cmd, int **pipes, int i, int n_cmds, t_env *env)
{
	char	*path;
	char	**envp;

	setup_pipe_fds(pipes, i, n_cmds);
	close_all_pipes(pipes, n_cmds - 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = resolve_executable(cmd[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2)
		exit(127);
	}
	envp = env_to_envp(env);
	if (!envp)
		exit(1);
	execve(path, cmd, envp);
	perror(cmd[0]);
	exit(126);
}

int	wait_all(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &status, 0) != -1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
	return (last_status);
}
