/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:25:12 by fluca             #+#    #+#             */
/*   Updated: 2025/11/13 17:13:38 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}	t_node_type;

typedef struct s_redir
{
	t_token_type		type;
	char				*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	char			**argv;
	t_redir			*redirs;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*ast_new_cmd(void);
t_ast	*ast_new_pipe(t_ast *left, t_ast *right);
void	ast_clear(t_ast **ast);
t_redir	*redir_new(t_token_type type, char *target);
void	redir_add_back(t_redir **lst, t_redir *new);
void	redir_clear(t_redir **lst);

#endif