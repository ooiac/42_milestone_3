#include "../../include/minishell.h"

int	builtin_cd(char **args, t_env **env)
{
	char	*path;
	(void)env;
	if (!args[1])
	{
		path = getenv("HOME")
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (1);
	}
}
