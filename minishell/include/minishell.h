/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:44:30 by caida-si          #+#    #+#             */
/*   Updated: 2025/11/10 18:11:23 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

/* env management */
t_env	*env_from_envp(char **envp);
void	free_env(t_env *env);
char	*env_get(t_env *env, const char *key);

/* main loop */
void	start_shell(t_env *env);


#endif