/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:21 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/15 16:23:04 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	translate_status(int status)
{
	if (WIFEXITED(status))
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

static int	handle_exec_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (errno == EACCES)
	{
		ft_putendl_fd("Permission denied", 2);
		return (126);
	}
	else if (errno == EISDIR)
	{
		ft_putendl_fd("Is a directory", 2);
		return (126);
	}
	ft_putendl_fd("command not found", 2);
	return (127);
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
		return (handle_exec_error(av[0]));
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
	int			**pipes;
	pid_t		*pids;
	int			n_cmds;
	int			i;
	t_pipe_ctx	ctx;

	n_cmds = 0;
	while (cmds[n_cmds])
		n_cmds++;
	pipes = create_pipes(n_cmds - 1);
	pids = malloc(sizeof(pid_t) * n_cmds);
	ctx.pipes = pipes;
	ctx.n_cmds = n_cmds;
	ctx.env = env;
	i = 0;
	while (i < n_cmds)
	{
		ctx.i = i;
		pids[i] = fork();
		if (pids[i] == 0)
			exec_in_pipeline(cmds[i], &ctx);
		i++;
	}
	close_all_pipes(pipes, n_cmds - 1);
	return (wait_all(pids, n_cmds));
}
