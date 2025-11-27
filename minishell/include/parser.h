/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:25:49 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:19:45 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "ast.h"
# include "libft.h"

int		parser_check_syntax(t_token *tok);
t_ast	*parse_pipeline(t_token **tok);
t_ast	*parse_command(t_token **tok);

#endif