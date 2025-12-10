/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:10:45 by fluca             #+#    #+#             */
/*   Updated: 2025/12/10 16:12:47 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*append_str(char *result, char *str)
{
	char	*new;

	if (!str)
		return (result);
	new = ft_strjoin(result, str);
	free(result);
	free(str);
	return (new);
}
