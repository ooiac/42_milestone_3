/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:38:13 by fluca             #+#    #+#             */
/*   Updated: 2025/11/12 18:38:13 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *lexer_tokenize(const char *line)
{
    t_token *head;
    int     i;

    *head = NULL;
    i = 0;

    while(line[i])
    {
        if (is_whitespace(line[i]))
            i++;
        else if (is_operator_char(line[i]))
        {
            t_token_type type;
            char *op = read_operator(line, &I, &type);
            token_add_back(&head, token_new(type, op));
        }
        else
        {
            char *word = read_word(line, &i);
            if (!word)
                return(token_clear(&head), NULL);
            token_add_back(&head, token_new(T_WORD, word));
        }
    }
    return(head);
}

