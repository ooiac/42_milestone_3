/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:11:54 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:22:53 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	handle_less(const char *line, int *i, t_token_type *type)
{
	if (line[*i + 1] == '<')
	{
		*type = T_HEREDOC;
		(*i) += 2;
	}
	else
	{
		*type = T_REDIR_IN;
		(*i)++;
	}
}

static void	handle_greater(const char *line, int *i, t_token_type *type)
{
	if (line[*i + 1] == '>')
	{
		*type = T_REDIR_APPEND;
		(*i) += 2;
	}
	else
	{
		*type = T_REDIR_OUT;
		(*i)++;
	}
}

static char	*read_pipe_or_or(const char *line, int *i, t_token_type *type)
{
	int	start;

	start = *i;
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		*type = T_OR;
		(*i) += 2;
	}
	else if (line[*i] == '|')
	{
		*type = T_PIPE;
		(*i)++;
	}
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}

static char	*read_and(const char *line, int *i, t_token_type *type)
{
	int	start;

	start = *i;
	if (line[*i] == '&' && line[*i + 1] == '&')
	{
		*type = T_AND;
		(*i) += 2;
	}
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}

char	*read_operator(const char *line, int *i, t_token_type *type)
{
	int	start;

	start = *i;
	if (line[*i] == '|')
		return (read_pipe_or_or(line, i, type));
	if (line[*i] == '&')
		return (read_and(line, i, type));
	if (line[*i] == '<')
		handle_less(line, i, type);
	else if (line[*i] == '>')
		handle_greater(line, i, type);
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}
