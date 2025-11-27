/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:21:23 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:03:22 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	skip_quoted(const char *line, int *i, char quote_char)
{
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i] == quote_char)
		(*i)++;
}

static void	handle_less(const char *line, int *i, t_token_type *type)
{
	if (line[*i] == '<')
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
}

static void	handle_greater(const char *line, int *i, t_token_type *type)
{
	if (line[*i] == '>')
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
}

static char	*read_less_greater(const char *line, int *i, t_token_type *type)
{
	int	start;

	start = *i;
	if (line[*i] == '<')
		handle_less(line, i, type);
	else if (line[*i] == '>')
		handle_greater(line, i, type);
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}

static char	*read_pipe(const char *line, int *i, t_token_type *type)
{
	int	start;

	start = *i;
	if (line[*i] == '|')
	{
		*type = T_PIPE;
		(*i)++;
	}
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}

char	*read_operator(const char *line, int *i, t_token_type *type)
{
	if (line[*i] == '|')
		return (read_pipe(line, i, type));
	return (read_less_greater(line, i, type));
}

char	*read_word(const char *line, int *i)
{
	int		start;
	int		in_quote;
	char	quote_char;

	start = *i;
	in_quote = 0;
	quote_char = 0;
	while (line[*i])
	{
		if (!in_quote && is_operator_char(line[*i]))
			break ;
		if (!in_quote && is_whitespace(line[*i]))
			break ;
		if (!in_quote && (line[*i] == '\'' || line[*i] == '"'))
		{
			in_quote = 1;
			quote_char = line[*i];
			(*i)++;
			skip_quoted(line, i, quote_char);
			in_quote = 0;
			continue ;
		}
		(*i)++;
	}
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}
