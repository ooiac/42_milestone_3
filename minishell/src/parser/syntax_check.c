/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:31:59 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:27:06 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	has_fd_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i > 0 && (str[i] == '>' || str[i] == '<'))
		return (1);
	return (0);
}

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

static int	check_fd_redirections(t_token *tok)
{
	if (tok->type == T_WORD && has_fd_number(tok->value))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("file descriptor redirections not supported", 2);
		return (-1);
	}
	return (0);
}

static int	check_operator_position(t_token *tok)
{
	if (tok->type == T_PIPE || tok->type == T_AND || tok->type == T_OR)
	{
		if (!tok->next)
		{
			ft_putendl_fd("Syntax error: unexpected end after operator", 2);
			return (-1);
		}
		if (tok->next->type == T_PIPE || tok->next->type == T_AND
			|| tok->next->type == T_OR)
		{
			ft_putendl_fd("Syntax error: unexpected operator", 2);
			return (-1);
		}
	}
	return (0);
}

int	parser_check_syntax(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == T_PIPE || tok->type == T_AND || tok->type == T_OR)
	{
		ft_putendl_fd("Syntax error: unexpected operator at start", 2);
		return (-1);
	}
	while (tok)
	{
		if (check_fd_redirections(tok) != 0)
			return (-1);
		if (check_redir_target(tok) != 0)
			return (-1);
		if (check_operator_position(tok) != 0)
			return (-1);
		tok = tok->next;
	}
	return (0);
}
