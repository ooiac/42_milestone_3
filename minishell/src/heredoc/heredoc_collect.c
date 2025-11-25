/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:05:51 by fluca             #+#    #+#             */
/*   Updated: 2025/11/21 19:05:43 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "signals.h"
#include "libft.h"

static char *append_line(char *content, char *line)
{
    char    *tmp;
    char    *new;

    if (!content)
        tmp = ft_strdup("");
    else
        tmp = content;
    new = ft_strjoin(tmp, line);
    if(content)
        free(content);
    free(tmp);
    tmp = new;
    new = ft_strjoin(tmp, "\n");
    free(tmp);
    return (new);
}

static int  check_delimiter(char *line, char *delimiter, size_t delim_len)
{
    return (ft_strncmp(line, delimiter, delim_len) == 0
        && line[delim_len] == '\0');
}

static char *handle_signal_interrupt(char *content)
{
    free(content);
    g_signal_received = 0;
    setup_signals_prompt();
    return (NULL);
}

static char	*process_line(char *line, char *content, char *delimiter,
        size_t delim_len)
{
    if (!line)
    {
        ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
        return (content);
    }
    if (check_delimiter(line, delimiter, delim_len))
    {
        free(line);
        return (content);
    }
    content = append_line(content, line);
    free(line);
    return (NULL);
}

char	*collect_heredoc(char *delimiter, int expand)
{
    char	*line;
    char	*content;
    char	*result;
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
        result = process_line(line, content, delimiter, delim_len);
        if (result)
        {
            content = result;
            break ;
        }
        content = result;
    }
    setup_signals_prompt();
    return (content);
}
