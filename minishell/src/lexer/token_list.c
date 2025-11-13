/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:21:33 by fluca             #+#    #+#             */
/*   Updated: 2025/11/13 11:45:56 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(t_token_type type, char *value)
{
    t_token *new = malloc(sizeof(t_token));
    if(!new)
        return(NULL);
    new->type = type;
    new->value = value;
    new->next = NULL;
    return(new);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token *tmp;

    if (!lst || !new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    token_clear(t_token **lst)
{
    t_token *tmp;

    while (lst && *lst)
    {
        tmp = (*lst)->next;
        free((*lst)->value);
        free((*lst));
        *lst = tmp;
    }
}