/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:17:30 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 20:06:55 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static int  process_redir_heredocs(t_redir *redir, char **env, int exit_status)
{
    char    *delimiter;
    char    *content;
    int     expand;

    while (redir)
    {
        if (redir->type == T_HEREDOC)
        {
            expand = !has_quotes(redir->target);
            delimiter = remove_quotes(redir->target);
            content = collect_heredoc(delimiter, expand);
            free(delimiter);
            if(!content)
                return (-1);
            if (expand)
            {
                char *expanded = expand_heredoc_line(content, env, exit_status);
                free(content);
                content = expanded;
            }
            free(content);
        }
        redir = redir->next;
    }
    return (0);
}

static int  process_cmd_heredocs(t_ast *ast, char **env, int exit_status)
{
    if(ast->redirs)
        return (process_redir_heredocs(ast->redirs, env, exit_status));
    return (0);
}

int process_heredocs(t_ast *ast, char **env, int exit_status)
{
    if(!ast)
        return (0);
    if (ast->type == NODE_PIPE)
    {
        if(process_heredocs(ast->left, env, exit_status) != 0)
            return (-1);
        if(process_heredocs(ast->right, env, exit_status) != 0)
            return (-1);
    }
    else
        return (process_cmd_heredocs(ast, env, exit_status));
    return (0);
}
