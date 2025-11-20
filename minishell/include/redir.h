/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:50:51 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:50:53 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

#include "minishell.h"

int	open_redir_in(const char *file)
{
	int fd;

	fd = open(file, ORDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
	}
	return (fd);
}

int	open_redir_out(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
	}
	return(fd);
}

int	open_redir_append(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
	}
	return (fd);
}

#endif /* REDIR_H */
