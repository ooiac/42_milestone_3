#include "../include/minishell.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, cmd);
	free(tmp);
	return (joined);
}

char	*resolve_executable(const char *cmd, t_env)
{
	
}