/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:55:12 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/02 14:21:46 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*tokenize_and_parse(char *line, t_token **tokens)
{
	t_ast	*ast;

	*tokens = lexer_tokenize(line);
	if (!*tokens)
		return (NULL);
	if (parser_check_syntax(*tokens) != 0)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		token_clear(tokens);
		return (NULL);
	}
	ast = parse_pipeline(tokens);
	token_clear(tokens);
	return (ast);
}

static int	expand_and_exec(t_ast *ast, t_env **env, int last_status)
{
	char	**envp;
	int		status;

	envp = env_to_envp(*env);
	if (process_heredocs(ast, envp, last_status) != 0)
	{
		free_envp(envp);
		ast_clear(&ast);
		return (1);
	}
	expand_ast(ast, envp, last_status);
	free_envp(envp);
	status = exec_ast(ast, env);
	ast_clear(&ast);
	return (status);
}

static int	process_line(char *line, t_env **env, int last_status)
{
	t_token	*tokens;
	t_ast	*ast;

	ast = tokenize_and_parse(line, &tokens);
	if (!ast)
		return (last_status);
	return (expand_and_exec(ast, env, last_status));
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
