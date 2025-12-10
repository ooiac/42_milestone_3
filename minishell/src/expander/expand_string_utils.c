/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:10:45 by fluca             #+#    #+#             */
/*   Updated: 2025/12/03 13:10:45 by fluca            ###   ########.fr       */
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
