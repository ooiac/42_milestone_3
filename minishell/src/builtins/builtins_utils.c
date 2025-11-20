/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:14 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 13:38:15 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int	exec_builtin(char **args, t_env **env)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (builtin_echo(args));
    if (ft_strcmp(args[0], "cd") == 0)
        return (builtin_cd(args, env));
    if (ft_strcmp(args[0], "pwd") == 0)
        return (builtin_pwd());
    if (ft_strcmp(args[0], "export") == 0)
        return (builtin_export(args, env));
    if (ft_strcmp(args[0], "unset") == 0)
        return (builtin_unset(args, env));
    if (ft_strcmp(args[0], "env") == 0)
        return (builtin_env(*env));
    if (ft_strcmp(args[0], "exit") == 0)
        return (builtin_exit(args));
    return (1);
}
