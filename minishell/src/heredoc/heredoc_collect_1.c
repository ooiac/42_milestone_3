/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:05:51 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:47:12 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_line(char *content, char *line)
{
	char	*tmp;
	char	*new;

	if (!content)
		tmp = ft_strdup("");
	else
		tmp = content;
	new = ft_strjoin(tmp, line);
	if (tmp != content)
		free(tmp);
	tmp = new;
	new = ft_strjoin(tmp, "\n");
	free(tmp);
	return (new);
}

int	check_delimiter(char *line, char *delimiter, size_t delim_len)
{
	return (ft_strncmp(line, delimiter, delim_len) == 0
		&& line[delim_len] == '\0');
}

char	*handle_eof_or_delim(char *line, char *content, char *delim)
{
	if (!line)
	{
		ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
		return (content);
	}
	if (check_delimiter(line, delim, ft_strlen(delim)))
	{
		free(line);
		return (content);
	}
	return (NULL);
}
