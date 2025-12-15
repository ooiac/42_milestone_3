/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:02:36 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/15 16:23:04 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	apply_output_redir(t_redir *tmp)
{
	int	fd;

	fd = open_redir_file(tmp);
	if (fd < 0)
		return (-1);
	if (!has_output_redir_after(tmp))
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == T_REDIR_IN)
		{
			if (apply_redir_in(tmp) < 0)
				return (-1);
		}
		else if (tmp->type == T_REDIR_OUT || tmp->type == T_REDIR_APPEND)
		{
			if (apply_output_redir(tmp) < 0)
				return (-1);
		}
		else if (tmp->type == T_HEREDOC && tmp->heredoc_fd >= 0)
		{
			dup2(tmp->heredoc_fd, STDIN_FILENO);
			close(tmp->heredoc_fd);
		}
		tmp = tmp->next;
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
