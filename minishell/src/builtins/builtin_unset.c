/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:05 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 15:32:32 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_env_node(char *key, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	if (!*env)
		return ;
	if (ft_strcmp((*env)->key, key) == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
		return ;
	}
	prev = *env;
	tmp = (*env)->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			prev->next = tmp->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	builtin_unset(char **args, t_env **env)
{
	int i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		remove_env_node(args[i], env);
		i++;
	}
	return (0);
}
