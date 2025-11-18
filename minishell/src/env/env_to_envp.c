/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:36:04 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/13 17:36:10 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	env_count(t_env *env)
{
	int count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	free_envp(char **envp)
{
	int i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		size;
	int		i;

	size = env_count(env);
	envp = malloc((size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (free_envp(envp), NULL);
		envp[i] = ft_strjoin(tmp, env->val);
		free(tmp);
		if (!envp[i])
			return (free_envp(envp), NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
