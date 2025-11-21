/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:25:02 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 20:26:28 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"

char    *expand_heredoc_line(char *line, char **env, int exit_status)
{
    return (expand_string(line, env, exit_status));
}