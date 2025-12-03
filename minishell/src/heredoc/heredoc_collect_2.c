/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:06:21 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:07:19 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*read_heredoc_loop(char *delimiter, char *content)
{
	char	*line;
	char	*result;

	while (1)
	{
		line = readline("> ");
		if (g_signal_received == SIGINT)
		{
			free(content);
			g_signal_received = 0;
			return (NULL);
		}
		result = handle_eof_or_delim(line, content, delimiter);
		if (result || !line)
			return (result);
		content = append_line(content, line);
		free(line);
	}
	return (content);
}

char	*collect_heredoc(char *delimiter, int expand)
{
	char	*content;

	(void)expand;
	setup_signals_heredoc();
	content = read_heredoc_loop(delimiter, NULL);
	setup_signals_prompt();
	return (content);
}
