//
// Created by rbonneva on 30/01/23.
//

#include "../../incs/mini_shell.h"

t_error	get_path(t_lstd *current, t_lstd *env_dict)
{
	char **paths;

	if (access(get(current)->cmd[0], X_OK) == 0)
	{
		get(current)->path = ft_strdup(get(current)->cmd[0]);
		if (!get(current)->path)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
	//TODO [Aurel] set env as a dictionary before
	paths = get_env_dict(ft_lstd_find(env_dict, "PATH", find)->content)->value;
	while (paths)
	{
		get(current)->path = ft_strjoin(paths[0], get(current)->cmd[0]);
		if (!get(current)->path)
			return (MALLOC_ERROR);
		if (access(get(current)->path, X_OK) == 0)
			return (SUCCESS);
		get(current)->path = ft_free(get(current)->path);
		paths++;
	}
	return (SUCCESS);
}