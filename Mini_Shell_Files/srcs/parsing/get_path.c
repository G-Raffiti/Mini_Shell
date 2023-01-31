//
// Created by rbonneva on 30/01/23.
//

#include "../../incs/mini_shell.h"

t_error	get_path(t_mini_shell *ms, t_cmd *cmd)
{
	int i;

	if (access(cmd->cmd[0], X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->cmd[0]);
		if (!cmd->path)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	i = -1;
	if (!ms->paths)
		return (SUCCESS);
	while (ms->paths[++i])
	{
		cmd->path = ft_strjoin(ms->paths[i], cmd->cmd[i]);
		if (!cmd->path)
			return (MALLOC_ERROR);
		if (access(cmd->path, X_OK) == 0)
			return (SUCCESS);
		cmd->path = ft_free(cmd->path);
		i++;
	}
	return (SUCCESS);
}