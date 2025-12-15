/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:44:03 by fluca             #+#    #+#             */
/*   Updated: 2025/12/15 16:23:04 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_argv(char **argv, char **env, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv[i])
	{
		expanded = expand_string(argv[i], env, exit_status);
		free(argv[i]);
		argv[i] = expanded;
		i++;
	}
}

static void	remove_empty_args(t_ast *ast)
{
	int	i;
	int	j;

	if (!ast->argv)
		return ;
	i = 0;
	j = 0;
	while (ast->argv[i])
	{
		if (ast->argv[i][0] != '\0')
		{
			ast->argv[j] = ast->argv[i];
			j++;
		}
		else
			free(ast->argv[i]);
		i++;
	}
	ast->argv[j] = NULL;
}

static void	expand_redirs(t_redir *redir, char **env, int exit_status)
{
	char	*expanded;

	while (redir)
	{
		expanded = expand_string(redir->target, env, exit_status);
		free(redir->target);
		redir->target = expanded;
		redir = redir->next;
	}
}

static void	expand_command(t_ast *ast, char **env, int exit_status)
{
	if (ast->argv)
	{
		expand_argv(ast->argv, env, exit_status);
		remove_empty_args(ast);
	}
	if (ast->redirs)
		expand_redirs(ast->redirs, env, exit_status);
}

void	expand_ast(t_ast *ast, char **env, int exit_status)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE || ast->type == NODE_AND || ast->type == NODE_OR)
	{
		expand_ast(ast->left, env, exit_status);
		expand_ast(ast->right, env, exit_status);
	}
	else
		expand_command(ast, env, exit_status);
}
