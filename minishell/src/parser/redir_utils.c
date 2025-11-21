/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:59:17 by fluca             #+#    #+#             */
/*   Updated: 2025/11/13 18:11:38 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir *redir_new(t_token_type type, char *target)
{
    t_redir *node;

    node = malloc(sizeof(t_redir));
    if(!node)
        return(NULL);
    node->type = type;
    node->target = target;
    node->next = NULL;
    return(node);
}

void    redir_add_back(t_redir **lst, t_redir *new)
{
    t_redir *tmp;

    if(!lst || !new)
        return ;
    if(!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void    redir_clear(t_redir **lst)
{
    t_redir *tmp;

    if(!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->target);
        free(*lst);
        *lst = tmp;
    }
}