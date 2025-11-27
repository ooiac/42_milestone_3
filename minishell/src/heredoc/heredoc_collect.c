/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:05:51 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:03:22 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_line(char *content, char *line)
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

static int	check_delimiter(char *line, char *delimiter, size_t delim_len)
{
	return (ft_strncmp(line, delimiter, delim_len) == 0
		&& line[delim_len] == '\0');
}

static char	*handle_signal_interrupt(char *content)
{
	free(content);
	g_signal_received = 0;
	setup_signals_prompt();
	return (NULL);
}

char	*collect_heredoc(char *delimiter, int expand)
{
	char	*line;
	char	*content;
	size_t	delim_len;

	(void)expand;
	content = NULL;
	delim_len = ft_strlen(delimiter);
	setup_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == SIGINT)
			return (handle_signal_interrupt(content));
		if (!line)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (check_delimiter(line, delimiter, delim_len))
		{
			free(line);
			break ;
		}
		content = append_line(content, line);
		free(line);
	}
	setup_signals_prompt();
	return (content);
}
