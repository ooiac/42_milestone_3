/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:17:30 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 17:49:33 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	write_heredoc_content(int fd, char *content)
{
	if (content)
	{
		write(fd, content, ft_strlen(content));
		free(content);
	}
	return (0);
}

static int	process_single_heredoc(t_redir *redir, char **env, int exit_status)
{
	char	*delimiter;
	char	*content;
	char	*expanded;
	int		expand;
	int		pipefd[2];

	expand = !has_quotes(redir->target);
	delimiter = remove_quotes(redir->target);
	content = collect_heredoc(delimiter, expand);
	free(delimiter);
	if (!content)
		return (-1);
	if (expand)
	{
		expanded = expand_heredoc_line(content, env, exit_status);
		free(content);
		content = expanded;
	}
	if (pipe(pipefd) < 0)
		return (free(content), -1);
	write_heredoc_content(pipefd[1], content);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

static int	process_redir_heredocs(t_redir *redir, char **env, int exit_status)
{
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			if (process_single_heredoc(redir, env, exit_status) != 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	process_cmd_heredocs(t_ast *ast, char **env, int exit_status)
{
	if (ast->redirs)
		return (process_redir_heredocs(ast->redirs, env, exit_status));
	return (0);
}

int	process_heredocs(t_ast *ast, char **env, int exit_status)
{
	if (!ast)
		return (0);
	if (ast->type == NODE_PIPE)
	{
		if (process_heredocs(ast->left, env, exit_status) != 0)
			return (-1);
		if (process_heredocs(ast->right, env, exit_status) != 0)
			return (-1);
	}
	else
		return (process_cmd_heredocs(ast, env, exit_status));
	return (0);
}
