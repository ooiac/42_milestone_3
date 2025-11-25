/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:34:59 by fluca             #+#    #+#             */
/*   Updated: 2025/11/19 20:00:34 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int var_name_len(char *str)
{
    int len;

    len = 0;
    if (str[len] == '?')
        return (1);
    if(!ft_isalpha(str[len]) && str[len] != '_')
        return (0);
    while(str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
        len++;
    return (len);
}

static char *get_var_name(char *str, int len)
{
    char    *var_name;

    var_name = malloc(len + 1);
    if(!var_name)
        return(NULL);
    ft_strlcpy(var_name, str, len + 1);
    return (var_name);
}

static  char *handle_exit_status(int exit_status)
{
    return (ft_itoa(exit_status));
}

char    *expand_variable(char *str, int *i, char **env, int exit_status)
{
    int		len;
	char	*var_name;
	char	*var_value;

	(*i)++;
	if(str[*i] == '?')
	{
		(*i)++;
		return (handle_exit_status(exit_status));
	}
	len = var_name_len(&str[*i]);
	if(len == 0)
		return (ft_strdup("$"));
	var_name = get_var_name(&str[*i], len);
	*i += len;
	var_value = get_env_value(var_name, env);
	free(var_name);
	if(!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}