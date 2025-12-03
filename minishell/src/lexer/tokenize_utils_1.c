/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:21:23 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:44:33 by fluca            ###   ########.fr       */
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

void	skip_quoted(const char *line, int *i, char quote_char)
{
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i] == quote_char)
		(*i)++;
}
