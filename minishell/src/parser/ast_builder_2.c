/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:14:05 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:18:34 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*extract_redirs(t_token **tok)
{
	t_redir	*head;
	t_redir	*new;

	head = NULL;
	while (*tok && (*tok)->type != T_PIPE)
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
	t_ast	*pipe_node;

	left = parse_command(tok);
	if (!left)
		return (NULL);
	if (*tok && (*tok)->type == T_PIPE)
	{
		*tok = (*tok)->next;
		pipe_node = ast_new_pipe(left, parse_pipeline(tok));
		return (pipe_node);
	}
	return (left);
}
