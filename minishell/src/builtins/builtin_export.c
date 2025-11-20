/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:37:58 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:47:46 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_sorted_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x", 1);
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(env->val, 1);
		ft_putendl_fd("\"", 1);
		env = env->next;
	}
}

static int	add_or_update_env(char *arg, t_env **env)
{
	char	*equal;
	char	*key;
	char	*val;
	t_env	*new;
	t_env	*tmp;

	equal = ft_strchr(arg, '=')
	if (!equal)
		return (0);
	key = ft_substr(arg, 0, equal - arg);
	val = ft_strdup(equal + 1);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->val);
			tmp->val = val;
			return (free(key), 0);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	new->key = key;
	new->val = val;
	new->next = *env;
	*env = new;
	return (0);
}

int	builtin_export(char **args, t_env **env)
{
	int	i;

	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		add_or_update_env(args[i], env);
		i++
	}
	return (0);
}
