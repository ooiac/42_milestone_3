/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:11:48 by fluca             #+#    #+#             */
/*   Updated: 2025/12/02 14:06:57 by fluca            ###   ########.fr       */
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
char	*append_line(char *content, char *line);
int		check_delimiter(char *line, char *delimiter, size_t delim_len);
char	*handle_eof_or_delim(char *line, char *content, char *delim);

#endif