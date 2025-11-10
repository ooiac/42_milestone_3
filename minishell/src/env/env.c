/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:37:13 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/10 19:02:36 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*new_env_node(char *entry)
{
	t_env	*node;
	char	*sep;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	sep = ft_strchr(entry, '=');
	if (!sep)
		return (free(node), NULL);
	key_len = sep - entry;
	node->key = ft_substr(entry, 0, key_len);
	node->val = ft_strdup(sep + 1);
	node->next = NULL;
	if (!node->key || !node->val)
		return (free(node->key), free(node->val), free(node), NULL);
	return (node);
}

t_env	*env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = new_env_node(envp[i]);
		if (!node)
			return (free_env(head), NULL);
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = tmp;
	}
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}