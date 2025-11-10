/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:16:30 by caida-si          #+#    #+#             */
/*   Updated: 2025/06/16 13:40:25 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (*n == '\0')
		return ((char *)h);
	i = 0;
	while (h[i] && i < len)
	{
		j = 0;
		while (n[j] && h[i + j] == n[j] && (i + j) < len)
			j++;
		if (!n[j])
			return ((char *)&h[i]);
		i++;
	}
	return (NULL);
}
