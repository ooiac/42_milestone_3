/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:49:52 by fluca             #+#    #+#             */
/*   Updated: 2025/11/19 19:56:19 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

char    *get_env_value(char *var, char **env)
{
    int i;
    int len;

    if(!var || !env)
        return (NULL);
    len = ft_strlen(var);
    i = 0;
    while (env[i])
    {
        if(ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return (&env[i][len + 1]);
        i++;
    }
    return (NULL);
}
