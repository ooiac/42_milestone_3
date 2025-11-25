/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:16:44 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 20:38:31 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int has_quotes(char *delimiter)
{
    int i;

    i = 0;
    while (delimiter[i])
    {
        if(delimiter[i] == '\'' || delimiter[i] == '"')
            return (1);
        i++;
    }
    return (0);
}

char    *remove_quotes(char *delimiter)
{
    char    *result;
    int     i;
    int     j;

    result = malloc(ft_strlen(delimiter) + 1);
    if(!result)
        return (NULL);
    i = 0;
    j = 0;
    while (delimiter[i])
    {
        if (delimiter[i] != '\'' && delimiter[i] != '"')
        {
            result[j] = delimiter[i];
            j++;
        }
        i++;
    }
    result[j] = '\0';
    return (result);
}
