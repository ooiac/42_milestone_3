/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:55:12 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/25 21:04:14 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_line(char *line, t_env **env, int last_status)
{
	t_token	*tokens;
	t_ast	*ast;
	char	**envp;
	int		status;

	tokens = lexer_tokenize(line);
	if (!tokens)
		return (last_status);
	if (!parser_check_syntax(tokens))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		token_clear(&tokens);
		return (2);
	}
	ast = parse_pipeline(&tokens);
	token_clear(&tokens);
	if (!ast)
		return (last_status);
	envp = env_to_envp(*env);
	expand_ast(ast, envp, last_status);
	free_envp(envp);
	status = exec_ast(ast, env);
	ast_clear(&ast);
	return (status);
}

void	start_shell(t_env *env)
{
	char	*line;
	int		status;

	status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			status = process_line(line, &env, status);
		}
		free(line);
	}
	ft_putendl_fd("exit", 1);
}
