/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:41:41 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:04:39 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*ast_new_cmd(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->argv = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*ast_new_pipe(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->argv = NULL;
	node->redirs = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	ast_clear(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->type == NODE_PIPE)
	{
		ast_clear(&(*ast)->left);
		ast_clear(&(*ast)->right);
	}
	else
	{
		free_argv((*ast)->argv);
		redir_clear(&(*ast)->redirs);
	}
	free(*ast);
	*ast = NULL;
}
