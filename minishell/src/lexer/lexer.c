/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:03:44 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 15:33:49 by caida-si         ###   ########.fr       */
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

static int	is_fd_redir(const char *word)
{
	int	i;

	i = 0;
	if (!word || !ft_isdigit(word[i]))
		return (0);
	while (word[i] && ft_isdigit(word[i]))
		i++;
	if (word[i] == '>' || word[i] == '<')
		return (1);
	return (0);
}

static int	handle_word(const char *line, int *i, t_token **head)
{
	char	*word;

	word = read_word(line, i);
	if (!word)
		return (-1);
	if (is_fd_redir(word))
	{
		free(word);
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("file descriptor redirections not supported", 2);
		return (-1);
	}
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
