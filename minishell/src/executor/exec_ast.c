/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:02:36 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/27 17:49:33 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	apply_redirections(t_redir *redirs)
{
	int		fd;

	while (redirs)
	{
		if (redirs->type == T_REDIR_IN)
		{
			fd = open(redirs->target, O_RDONLY);
			if (fd < 0)
				return (perror(redirs->target), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == T_REDIR_OUT)
		{
			fd = open(redirs->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redirs->target), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == T_REDIR_APPEND)
		{
			fd = open(redirs->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redirs->target), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == T_HEREDOC && redirs->heredoc_fd >= 0)
		{
			dup2(redirs->heredoc_fd, STDIN_FILENO);
			close(redirs->heredoc_fd);
		}
		redirs = redirs->next;
	}
	return (0);
}

static int	exec_simple_command(t_ast *ast, t_env **env)
{
	if (!ast->argv || !ast->argv[0])
		return (0);
	if (apply_redirections(ast->redirs) < 0)
		return (1);
	if (is_builtin(ast->argv[0]))
		return (exec_builtin(ast->argv, env));
	return (run_single_command(ast->argv, *env));
}

static int	exec_pipeline_recursive(t_ast *ast, t_env *env, int input_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (ast->type == NODE_CMD)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (apply_redirections(ast->redirs) < 0)
			exit(1);
		if (is_builtin(ast->argv[0]))
			exit(exec_builtin(ast->argv, &env));
		execve(resolve_executable(ast->argv[0], env), ast->argv,
			env_to_envp(env));
		exit(127);
	}
	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_pipeline_recursive(ast->left, env, input_fd);
		exit(1);
	}
	close(pipefd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, &status, 0);
	return (exec_pipeline_recursive(ast->right, env, pipefd[0]));
}

int	exec_ast(t_ast *ast, t_env **env)
{
	pid_t	pid;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast)
		return (0);
	if (ast->type == NODE_CMD)
	{
		if (is_builtin(ast->argv[0]))
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
			status = exec_simple_command(ast, env);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return (status);
		}
		if (ast->redirs)
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
			status = exec_simple_command(ast, env);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return (status);
		}
		return (exec_simple_command(ast, env));
	}
	pid = fork();
	if (pid == 0)
	{
		setup_signals_default();
		exec_pipeline_recursive(ast, *env, STDIN_FILENO);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
