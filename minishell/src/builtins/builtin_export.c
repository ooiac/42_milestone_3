/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:37:58 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/02 15:30:11 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

static void	create_env_node(char *key, char *val, t_env **env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->val = val;
	new->next = *env;
	*env = new;
}

static int	add_or_update_env(char *arg, t_env **env)
{
	char	*equal;
	char	*key;
	char	*val;
	t_env	*tmp;

	equal = ft_strchr(arg, '=');
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
	create_env_node(key, val, env);
	return (0);
}

int	builtin_export(char **args, t_env **env)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			add_or_update_env(args[i], env);
		i++;
	}
	return (ret);
}
