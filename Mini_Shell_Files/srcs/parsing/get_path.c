//
// Created by rbonneva on 30/01/23.
//

#include "../../incs/mini_shell.h"

t_error	get_path(t_cmd *cmd, t_lstd *env_dict)
{
	char **paths;

	if (access(cmd->cmd[0], X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->cmd[0]);
		if (!cmd->path)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
	//TODO [Aurel] set env as a dictionary before
	paths = get_env_dict(ft_lstd_find(env_dict, "PATH", find)->content)->value;
	while (paths)
	{
		cmd->path = ft_strjoin(paths[0], cmd->cmd[0]);
		if (!cmd->path)
			return (MALLOC_ERROR);
		if (access(cmd->path, X_OK) == 0)
			return (SUCCESS);
		cmd->path = ft_free(cmd->path);
		paths++;
	}
	return (SUCCESS);
}