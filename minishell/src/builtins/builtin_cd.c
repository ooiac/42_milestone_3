/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:37:46 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/27 17:27:27 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_env_var(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

static char	*handle_cd_minus(t_env *env)
{
	char	*oldpwd;

	oldpwd = env_get(env, "OLDPWD");
	if (!oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	ft_putendl_fd(oldpwd, 1);
	return (oldpwd);
}

static char	*get_cd_path(char **args, t_env *env)
{
	if (!args[1])
		return (env_get(env, "HOME"));
	if (ft_strcmp(args[1], "-") == 0)
		return (handle_cd_minus(env));
	return (args[1]);
}

int	builtin_cd(char **args, t_env **env)
{
	char	*path;
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	path = get_cd_path(args, *env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		if (args[1])
			perror(args[1]);
		else
			ft_putendl_fd("HOME not set", 2);
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		update_env_var(env, "OLDPWD", old_pwd);
		update_env_var(env, "PWD", new_pwd);
	}
	return (0);
}
