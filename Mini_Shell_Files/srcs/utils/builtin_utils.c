//
// Created by aurel on 2/4/23.
//

#include "../incs/mini_shell.h"

t_error	exec_builtin(t_mini_shell *ms, t_cmd *cmd)
{
	if (ft_str_cmp(cmd->cmd[0], "export") == 0)
	{
		if (export(ms, cmd) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else if (ft_str_cmp(cmd->cmd[0], "env") == 0)
		env(ms, cmd);
	return (SUCCESS);
}