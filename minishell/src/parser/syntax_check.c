/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:31:59 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:08:45 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	check_redir_target(t_token *tok)
{
	if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
		|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
	{
		if (!tok->next || tok->next->type != T_WORD)
		{
			ft_putendl_fd("Syntax error: Redirection without target", 2);
			return (-1);
		}
	}
	return (0);
}

static int	check_pipe_position(t_token *tok)
{
	if (tok->type == T_PIPE)
	{
		if (!tok->next)
		{
			ft_putendl_fd("Syntax error near unexpected token `|'", 2);
			return (-1);
		}
		if (tok->next->type == T_PIPE)
		{
			ft_putendl_fd("Syntax error near unexpected token `|'", 2);
			return (-1);
		}
	}
	return (0);
}

int	parser_check_syntax(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == T_PIPE)
	{
		ft_putendl_fd("Syntax error near unexpected token `|'", 2);
		return (-1);
	}
	while (tok)
	{
		if (check_redir_target(tok) != 0)
			return (-1);
		if (check_pipe_position(tok) != 0)
			return (-1);
		tok = tok->next;
	}
	return (0);
}
