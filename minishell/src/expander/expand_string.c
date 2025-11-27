/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:19:38 by fluca             #+#    #+#             */
/*   Updated: 2025/11/27 18:08:45 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*append_char(char *result, char c)
{
	char	*new;
	int		len;

	if (!result)
		len = 0;
	else
		len = ft_strlen(result);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	if (result)
	{
		ft_strlcpy(new, result, len + 1);
		free(result);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

static char	*append_str(char *result, char *str)
{
	char	*new;

	if (!str)
		return (result);
	new = ft_strjoin(result, str);
	free(result);
	free(str);
	return (new);
}

static char	*process_single_quote(char *str, int *i, char *result)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		result = append_char(result, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

static char	*process_double_quote(char *str, int *i, char *result,
			char **env, int exit_status)
{
	char	*var_value;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			var_value = expand_variable(str, i, env, exit_status);
			result = append_str(result, var_value);
		}
		else
		{
			result = append_char(result, str[*i]);
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

char	*expand_string(char *str, char **env, int exit_status)
{
	char	*result;
	char	*var_value;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = process_single_quote(str, &i, result);
		else if (str[i] == '"')
			result = process_double_quote(str, &i, result, env, exit_status);
		else if (str[i] == '$')
		{
			var_value = expand_variable(str, &i, env, exit_status);
			result = append_str(result, var_value);
		}
		else
		{
			result = append_char(result, str[i]);
			i++;
		}
	}
	return (result);
}
