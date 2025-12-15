/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:01 by caida-si          #+#    #+#             */
/*   Updated: 2025/12/15 09:55:48 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd(t_env *env)
{
	char	*pwd;
	char	cwd[1024];

	pwd = env_get(env, "PWD");
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}
