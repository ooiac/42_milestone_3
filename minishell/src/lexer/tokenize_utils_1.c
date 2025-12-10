/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:21:23 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:22:53 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

void	skip_quoted(const char *line, int *i, char quote_char)
{
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i] == quote_char)
		(*i)++;
}
