/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:25:02 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:03:22 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"

char	*expand_heredoc_line(char *line, char **env, int exit_status)
{
	return (expand_string(line, env, exit_status));
}
