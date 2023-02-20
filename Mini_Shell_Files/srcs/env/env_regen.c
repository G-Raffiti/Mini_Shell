//
// Created by rbonneva on 17/02/23.
//

//TODO : SHLVL -> si il est ft_unset il vaut 0 (+1 a la generation du nouvel ft_env)

#include "../../incs/mini_shell.h"

char	**regen_env(void)
{
	char **env;

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