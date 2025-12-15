/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:27:15 by fluca             #+#    #+#             */
/*   Updated: 2025/12/15 10:33:05 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_cmd_node(t_ast *ast, t_env *env, int input_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (apply_redirections(ast->redirs) < 0)
		exit(1);
	if (!ast->argv || !ast->argv[0])
		exit(0);
	if (is_builtin(ast->argv[0]))
		exit(exec_builtin(ast->argv, &env));
	execve(resolve_executable(ast->argv[0], env), ast->argv,
		env_to_envp(env));
	perror(ast->argv[0]);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(127);
}

static void	exec_pipe_child(t_ast *ast, t_env *env, int input_fd, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_pipeline_recursive(ast->left, env, input_fd);
	exit(1);
}

static void	wait_all_children(int *status)
{
	int	tmp_status;

	while (waitpid(-1, &tmp_status, 0) > 0)
	{
		if (WIFEXITED(tmp_status))
			*status = WEXITSTATUS(tmp_status);
		else if (WIFSIGNALED(tmp_status))
			*status = 128 + WTERMSIG(tmp_status);
	}
}

int	exec_pipeline_recursive(t_ast *ast, t_env *env, int input_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!ast)
	{
		status = 0;
		wait_all_children(&status);
		return (status);
	}
	if (ast->type == NODE_CMD)
		exec_cmd_node(ast, env, input_fd);
	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == 0)
		exec_pipe_child(ast, env, input_fd, pipefd);
	close(pipefd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (exec_pipeline_recursive(ast->right, env, pipefd[0]));
}
