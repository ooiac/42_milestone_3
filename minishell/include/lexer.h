/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:58:05 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 13:54:30 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token.h"
#include "libft.h"

t_token	*lexer_tokenize(const char *line);

int		is_operator_char(char c);
int		is_whitespace(char c);
char	*read_word(const char *line, int *i);
char	*read_pipe(const char *line, int *i, t_token_type *type);
char	*read_heredoc(const char *line, int *i, t_token_type *type);

#endif