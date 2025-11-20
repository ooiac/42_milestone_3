/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:55:12 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:57:55 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**split_simple(char *line)
{
	return (ft_split(line, ' '));
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	start_shell(t_env *env)
{
	char	*line;
	char	**args;
	int		status;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = split_simple(line);
		free(line);
		if (args && args[0])
		{
			if (is_builtin(args[0]))
				status = exec_builtin(args, &env);
			else
				status = run_single_command(args, env);
			(void)status;
		}
		free_args(args);
	}
	ft_putendl_fd("exit", 1);
}
