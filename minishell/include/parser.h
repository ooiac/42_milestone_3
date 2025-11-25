/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:25:49 by fluca             #+#    #+#             */
/*   Updated: 2025/11/13 17:15:32 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "ast.h"
# include "libft.h"

int     parser_check_syntax(t_token *tok);
t_ast   *parse_pipeline(t_token **tok);
t_ast   *parse_command(t_token **tok);

#endif