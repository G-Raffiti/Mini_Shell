//
// Created by rbonneva on 17/02/23.
//

#include "../../incs/mini_shell.h"

char	**regen_env(void)
{
	char	**env;

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, PWD_PATH_SIZE));
	if (!env[0])
		return (free_split(env));
	env[1] = ft_strdup("SHLVL=0");
	if (!env[1])
		return (free_split(env));
	env[2] = ft_strdup("_=/usr/bin/env");
	if (!env[2])
		return (free_split(env));
	return (env);
}

t_error	increase_shell_lvl(t_mini_shell *ms)
{
	int		i;
	char	*lvl;

	i = -1;
	while (ms->env[++i])
	{
		if (ft_strncmp(ms->env[i], "SHLVL", 5) == 0 && ms->env[i][5] == '=')
		{
			lvl = ft_itoa((ft_atoi(ms->env[i] + 6) + 1));
			if (!lvl)
				return (MALLOC_ERROR);
			ms->env[i] = ft_free(ms->env[i]);
			ms->env[i] = ft_strjoin("SHLVL=", lvl);
			if (!ms->env[i])
				return (MALLOC_ERROR);
			lvl = ft_free(lvl);
		}
	}
	return (SUCCESS);
}
