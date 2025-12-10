/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:14:05 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:22:53 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_logical_or_pipe(t_token_type type)
{
	return (type == T_PIPE || type == T_AND || type == T_OR);
}

t_redir	*extract_redirs(t_token **tok)
{
	t_redir	*head;
	t_redir	*new;

	head = NULL;
	while (*tok && !is_logical_or_pipe((*tok)->type))
	{
		if (is_redir_token((*tok)->type))
		{
			new = redir_new((*tok)->type, ft_strdup((*tok)->next->value));
			redir_add_back(&head, new);
			*tok = (*tok)->next;
		}
		*tok = (*tok)->next;
	}
	return (head);
}

t_ast	*parse_command(t_token **tok)
{
	t_ast	*node;
	t_token	*start;

	node = ast_new_cmd();
	if (!node)
		return (NULL);
	start = *tok;
	node->argv = extract_argv(&start);
	start = *tok;
	node->redirs = extract_redirs(&start);
	*tok = start;
	return (node);
}

t_ast	*parse_pipeline(t_token **tok)
{
	t_ast	*left;
	t_ast	*or_node;

	left = parse_and(tok);
	if (!left)
		return (NULL);
	if (*tok && (*tok)->type == T_OR)
	{
		*tok = (*tok)->next;
		or_node = ast_new_or(left, parse_pipeline(tok));
		return (or_node);
	}
	return (left);
}
