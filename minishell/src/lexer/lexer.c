/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:03:44 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:04:01 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_operator(const char *line, int *i, t_token **head)
{
	t_token_type	type;
	char			*op;

	op = read_operator(line, i, &type);
	token_add_back(head, token_new(type, op));
	return (0);
}

static int	handle_word(const char *line, int *i, t_token **head)
{
	char	*word;

	word = read_word(line, i);
	if (!word)
		return (-1);
	token_add_back(head, token_new(T_WORD, word));
	return (0);
}

t_token	*lexer_tokenize(const char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator_char(line[i]))
			handle_operator(line, &i, &head);
		else if (handle_word(line, &i, &head) < 0)
			return (token_clear(&head), NULL);
	}
	return (head);
}
