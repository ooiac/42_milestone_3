/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:02:36 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/02 14:42:31 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (perror(redir->target), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_redir_out(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == T_REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->target, flags, 0644);
	if (fd < 0)
		return (perror(redir->target), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == T_REDIR_IN)
		{
			if (apply_redir_in(redirs) < 0)
				return (-1);
		}
		else if (redirs->type == T_REDIR_OUT || redirs->type == T_REDIR_APPEND)
		{
			if (apply_redir_out(redirs) < 0)
				return (-1);
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

int	exec_simple_command(t_ast *ast, t_env **env)
{
	if (!ast->argv || !ast->argv[0])
		return (0);
	if (apply_redirections(ast->redirs) < 0)
		return (1);
	if (is_builtin(ast->argv[0]))
		return (exec_builtin(ast->argv, env));
	return (run_single_command(ast->argv, *env));
}
