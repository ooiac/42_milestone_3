/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:11:48 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 21:50:22 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "ast.h"
# include "libft.h"
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

int		process_heredocs(t_ast *ast, char **env, int exit_status);
char	*collect_heredoc(char *delemiter, int expand);
char	*expand_heredoc_line(char *line, char **env, int exit_status);
int		has_quotes(char *delimiter);
char	*remove_quotes(char *delimiter);

#endif