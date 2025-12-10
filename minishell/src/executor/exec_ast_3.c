/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:02:08 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:29:36 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_with_saved_fds(t_ast *ast, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	status = exec_simple_command(ast, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

static int	exec_pipeline_main(t_ast *ast, t_env **env)
{
	pid_t	pid;
	int		status;

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

static int	exec_and(t_ast *ast, t_env **env)
{
	int	status;

	status = exec_ast(ast->left, env);
	if (status == 0)
		return (exec_ast(ast->right, env));
	return (status);
}

static int	exec_or(t_ast *ast, t_env **env)
{
	int	status;

	status = exec_ast(ast->left, env);
	if (status != 0)
		return (exec_ast(ast->right, env));
	return (status);
}

int	exec_ast(t_ast *ast, t_env **env)
{
	if (!ast)
		return (0);
	if (ast->type == NODE_CMD)
	{
		if (!ast->argv || !ast->argv[0])
			return (0);
		if (is_builtin(ast->argv[0]) || ast->redirs)
			return (exec_with_saved_fds(ast, env));
		return (exec_simple_command(ast, env));
	}
	if (ast->type == NODE_AND)
		return (exec_and(ast, env));
	if (ast->type == NODE_OR)
		return (exec_or(ast, env));
	return (exec_pipeline_main(ast, env));
}
