/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:00:00 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/15 16:23:04 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (perror(redir->target), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	has_output_redir_after(t_redir *current)
{
	t_redir	*tmp;

	tmp = current->next;
	while (tmp)
	{
		if (tmp->type == T_REDIR_OUT || tmp->type == T_REDIR_APPEND)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	open_redir_file(t_redir *redir)
{
	int	flags;

	if (redir->type == T_REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	return (open(redir->target, flags, 0644));
}
