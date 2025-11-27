/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:38:13 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:03:22 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer_tokenize(const char *line)
{
	t_token			*head;
	int				i;
	t_token_type	type;
	char			*op;
	char			*word;

	head = NULL;
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator_char(line[i]))
		{
			op = read_operator(line, &i, &type);
			token_add_back(&head, token_new(type, op));
		}
		else
		{
			word = read_word(line, &i);
			if (!word)
				return (token_clear(&head), NULL);
			token_add_back(&head, token_new(T_WORD, word));
		}
	}
	return (head);
}
