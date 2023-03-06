//
// Created by aurel on 2/4/23.
//

#include "../../incs/mini_shell.h"

t_error	ft_env(t_mini_shell *ms)
{
	int	i;

	i = -1;
	while (ms->env && ms->env[++i])
		printf("%s\n", ms->env[i]);
	return (SUCCESS);
}
