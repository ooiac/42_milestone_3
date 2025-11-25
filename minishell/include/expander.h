/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:39:13 by fluca             #+#    #+#             */
/*   Updated: 2025/11/14 16:18:59 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ast.h"

void	expand_ast(t_ast *ast, char **env, int exit_status);
char	*expand_string(char *str, char **env, int exit_status);
char	*expand_variable(char *str, int *i, char **env, int exit_status);
char	*get_env_value(char *var, char **env);
int		is_quote(char c);
int		var_name_len(char *str);
#endif
