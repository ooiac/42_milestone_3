/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:02:08 by fluca             #+#    #+#             */
/*   Updated: 2025/12/03 13:48:12 by fluca            ###   ########.fr       */
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
	return (exec_pipeline_main(ast, env));
}