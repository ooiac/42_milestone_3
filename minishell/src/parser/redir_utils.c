/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:59:17 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:08:45 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*redir_new(t_token_type type, char *target)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->target = target;
	node->heredoc_fd = -1;
	node->next = NULL;
	return (node);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

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

void	redir_clear(t_redir **lst)
{
	t_redir	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->target);
		if ((*lst)->heredoc_fd >= 0)
			close((*lst)->heredoc_fd);
		free(*lst);
		*lst = tmp;
	}
}
