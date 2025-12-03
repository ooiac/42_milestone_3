/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:00:00 by fluca             #+#    #+#             */
/*   Updated: 2025/12/03 13:10:45 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	handle_quote_in_word(const char *line, int *i, int *in_quote)
{
	char	quote_char;

	quote_char = line[*i];
	(*i)++;
	skip_quoted(line, i, quote_char);
	*in_quote = 0;
}

char	*read_word(const char *line, int *i)
{
	int		start;
	int		in_quote;

	start = *i;
	in_quote = 0;
	while (line[*i])
	{
		if (!in_quote && is_operator_char(line[*i]))
			break ;
		if (!in_quote && is_whitespace(line[*i]))
			break ;
		if (!in_quote && (line[*i] == '\'' || line[*i] == '"'))
		{
			in_quote = 1;
			handle_quote_in_word(line, i, &in_quote);
			continue ;
		}
		(*i)++;
	}
	return (ft_substr(line, (unsigned int)start, (size_t)(*i - start)));
}
