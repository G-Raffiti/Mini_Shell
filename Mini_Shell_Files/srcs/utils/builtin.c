//
// Created by aurel on 2/4/23.
//

#include "../../incs/mini_shell.h"

t_error	exec_builtin(t_mini_shell *ms, t_cmd *cmd, int in_pipe)
{
	if (ft_str_cmp(cmd->cmd[0], "export") == 0)
	{
		if (ft_export(ms, cmd, in_pipe) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else if (ft_str_cmp(cmd->cmd[0], "env") == 0 && ms->env != NULL)
		env(ms, cmd, in_pipe);
	else if (ft_str_cmp(cmd->cmd[0], "unset") == 0)
		unset(ms, cmd, in_pipe);
	return (SUCCESS);
}