/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:30:00 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/10 15:22:53 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_pipeline_internal(t_token **tok)
{
	t_ast	*left;
	t_ast	*pipe_node;

	left = parse_command(tok);
	if (!left)
		return (NULL);
	if (*tok && (*tok)->type == T_PIPE)
	{
		*tok = (*tok)->next;
		pipe_node = ast_new_pipe(left, parse_pipeline_internal(tok));
		return (pipe_node);
	}
	return (left);
}

t_ast	*parse_and(t_token **tok)
{
	t_ast	*left;
	t_ast	*and_node;

	left = parse_pipeline_internal(tok);
	if (!left)
		return (NULL);
	if (*tok && (*tok)->type == T_AND)
	{
		*tok = (*tok)->next;
		and_node = ast_new_and(left, parse_and(tok));
		return (and_node);
	}
	return (left);
}
