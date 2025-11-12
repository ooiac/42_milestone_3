/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:21:23 by fluca             #+#    #+#             */
/*   Updated: 2025/11/12 18:21:23 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_whitespace(char c)
	return(c == ' ' || c == '<' || c == '\n');

int		is_operator_char(char c)
	return(c == '|' || c == '<' || c == '>');

char	*read_pipe(const char *line, int *i, t_token_type *type)
{
	int start;

	start = *i;
	if (line[*i] == '|')
	{
		*type = T_PIPE;
		(*i)++;
	}
	result = ft_substr(line + start, *i - start);
	return(result);
}	
char	*read_heredoc(const char *line, int *i, t_token_type *type)
{
	int start;

	start = *i;
	if (line[*i] == '<')
	{
		if(line[*i + 1] == '<')
			(*i)++, *type = T_HEREDOC;
		else
			*type = T_REDIR_IN;
		(*i)++;
	}
	else if(line[*i] == '>')
	{
		if(line[*i + 1] == '>')
			(*i)++, *type = T_REDIR_APPEND;
		else
			*type = T_REDIR_OUT;
		(*i)++;
	}
	result = ft_substr(line + start, *i - start);
	return(result);
}

char	*read_word(const char *line, int *i)
{
	int	star;
	int	in_quote;
	int	quote_char;

	star = *i;
	in_quote = 0;
	quote_char = 0;
	while (line[*i])
	{
		if(!in_quote && is_operator_char(line[*i]))
			break;
		if(!in_quote && is_whitespace(line[*i]))
			break;
		if (!in_quote && (line[*i] == '\'' || line[*i] == '"i'))
		{
			in_quote = 1;
			quote_char = line[*i];
		}
		else if (in_quote && line[*i] == quote_char)
			in_quote = 0;
		(*1)++;
	} 
	result = ft_substr(line + start, *i - start);
	return(result);
}