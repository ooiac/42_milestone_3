/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:11:50 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:45:27 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_HEREDOC);
}

static int	count_words(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			count++;
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
		{
			tok = tok->next;
			if (tok)
			{
				count--;
				tok = tok->next;
				continue ;
			}
		}
		tok = tok->next;
	}
	return (count);
}

static void	skip_redir(t_token **tok)
{
	*tok = (*tok)->next;
	if (*tok)
		*tok = (*tok)->next;
}

static int	process_token(t_token **tok, char **argv, int i)
{
	if ((*tok)->type == T_WORD)
	{
		argv[i] = ft_strdup((*tok)->value);
		*tok = (*tok)->next;
		return (i + 1);
	}
	else if (is_redir_token((*tok)->type))
		skip_redir(tok);
	else
		*tok = (*tok)->next;
	return (i);
}

char	**extract_argv(t_token **tok)
{
	char	**argv;
	int		count;
	int		i;

	count = count_words(*tok);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tok && (*tok)->type != T_PIPE)
		i = process_token(tok, argv, i);
	argv[i] = NULL;
	return (argv);
}
