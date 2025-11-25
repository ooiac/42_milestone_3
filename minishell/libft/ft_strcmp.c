/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:minishell/libft/ft_strcmp.c
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:38:49 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/20 15:35:40 by caida-si         ###   ########.fr       */
=======
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:58:05 by fluca             #+#    #+#             */
/*   Updated: 2025/11/13 15:00:09 by fluca            ###   ########.fr       */
>>>>>>> origin/fluca2:minishell/include/lexer.h
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD:minishell/libft/ft_strcmp.c
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
=======
t_token *lexer_tokenize(const char *line);

int   is_operator_char(char c);
int   is_whitespace(char c);
char  *read_word(const char *line, int *i);
char  *read_operator(const char *line, int *i, t_token_type *type);

#endif
>>>>>>> origin/fluca2:minishell/include/lexer.h
