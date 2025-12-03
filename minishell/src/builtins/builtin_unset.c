/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:05 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/02 12:16:04 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->val);
	free(node);
}

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
		free_env_node(tmp);
		return ;
	}
	prev = *env;
	tmp = (*env)->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			prev->next = tmp->next;
			free_env_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	builtin_unset(char **args, t_env **env)
{
	int	i;

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
