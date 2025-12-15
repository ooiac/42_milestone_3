/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:35:56 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/15 10:33:06 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/stat.h>

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, cmd);
	free(tmp);
	return (joined);
}

static void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*cmd_checker(const char *cmd)
{
	struct stat	path_stat;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			errno = EISDIR;
			return (NULL);
		}
		if (access(cmd, F_OK) != 0)
		{
			errno = ENOENT;
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		errno = EACCES;
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(const char *cmd, t_env *env)
{
	char	**paths;
	char	*full;
	char	*path_value;
	int		i;

	path_value = env_get(env, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], (char *)cmd);
		if (full && access(full, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*resolve_executable(const char *cmd, t_env *env)
{
	char	*direct;
	char	*found;
	int		saved_errno;

	direct = cmd_checker(cmd);
	if (direct)
		return (direct);
	if (ft_strchr(cmd, '/'))
	{
		saved_errno = errno;
		errno = saved_errno;
		return (NULL);
	}
	found = search_in_path(cmd, env);
	return (found);
}
