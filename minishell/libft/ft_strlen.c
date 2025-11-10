/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:33 by caida-si          #+#    #+#             */
/*   Updated: 2025/06/14 15:25:52 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/* int	main(void)
{
	char *str = "12345";
	char c = ft_strlen(str) + '0';  // converte 5 em '5'
	write(1, &c, 1);                // escreve o caractere '5'
	return (0);
} */