/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:11:50 by fluca             #+#    #+#             */
/*   Updated: 2025/11/14 14:28:59 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int  is_redir_token(t_token_type type)
{
    return(type == T_REDIR_IN || type == T_REDIR_OUT
        || type == T_REDIR_APPEND || type == T_HEREDOC);
}

static int  count_words(t_token *tok)
{
    int count;

    count = 0;
    while (tok && tok->type != T_PIPE)
    {
        if(tok->type == T_WORD)
            count++;
        if(tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
            || tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
        {
            tok = tok->next;
            if (tok)
            {
                count--;
                tok = tok->next;
                continue;
            }
        }
        tok = tok->next;
    }
    return(count);
}

static void skip_redir(t_token **tok)
{
    *tok = (*tok)->next;
    if(*tok)
        *tok = (*tok)->next;
}

static int  process_token(t_token **tok, char **argv, int i)
{
    if ((*tok)->type == T_WORD)
    {
        argv[i] = ft_strdup((*tok)->value);
        *tok = (*tok)->next;
        return(i + 1);
    }
    else if (is_redir_token((*tok)->type))
        skip_redir(tok);
    else
        *tok = (*tok)->next;
    return(i);
}

static char **extract_argv(t_token **tok)
{
    char    **argv;
    int     count;
    int     i;

    count = count_words(*tok);
    argv = malloc(sizeof(char *) * (count + 1));
    if(!argv)
        return(NULL);
    i = 0;
    while(*tok && (*tok)->type != T_PIPE)
        i = process_token(tok, argv, i);
    argv[i] = NULL;
    return(argv);
}

static t_redir  *extract_redirs(t_token **tok)
{
    t_redir *head;
    t_redir *new;

    head = NULL;
    while (*tok && (*tok)->type != T_PIPE)
    {
        if((*tok)->type == T_REDIR_IN || (*tok)->type == T_REDIR_OUT
            || (*tok)->type == T_REDIR_APPEND || (*tok)->type == T_HEREDOC)
        {
            new = redir_new((*tok)->type, ft_strdup((*tok)->next->value));
            redir_add_back(&head, new);
            *tok = (*tok)->next;
        }
        *tok = (*tok)->next;
    }
    return(head);
}

t_ast   *parse_command(t_token **tok)
{
    t_ast   *node;
    t_token *start;

    node = ast_new_cmd();
    if(!node)
        return(NULL);
    start = *tok;
    node->argv = extract_argv(&start);
    start = *tok;
    node->redirs = extract_redirs(&start);
    *tok = start;
    return(node);
}

t_ast *parse_pipeline(t_token **tok)
{
    t_ast   *left;
    t_ast   *pipe_node;

    left =parse_command(tok);
    if(!left)
        return(NULL);
    if(*tok && (*tok)->type == T_PIPE)
    {
        *tok = (*tok)->next;
        pipe_node = ast_new_pipe(left, parse_pipeline(tok));
        return(pipe_node);
    }
    return(left);
}