/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:30:00 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 17:01:27 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

t_token	*lexer_tokenize(const char *line);
int		is_whitespace(char c);
int		is_operator_char(char c);
char	*read_operator(const char *line, int *i, t_token_type *type);
char	*read_word(const char *line, int *i);

#endif
