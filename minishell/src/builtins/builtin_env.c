#include "../include/minishell.h"

int	builtin_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(env->val, 1);
		env = env->next;
	}
	return (0);
}
