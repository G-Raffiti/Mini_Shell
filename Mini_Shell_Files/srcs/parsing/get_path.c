//
// Created by rbonneva on 30/01/23.
//

#include "../../incs/mini_shell.h"

t_error	fill_paths(t_mini_shell *ms, char *full_path)
{
	char	*trunc_path;
	int		len;
	int		nbr_path;

	nbr_path = 0;
	while (*full_path)
	{
		len = 0;
		while (*full_path && *full_path != ':')
		{
			full_path++;
			len++;
		}
		trunc_path = ft_substr(full_path - len, 0, len);
		if (!trunc_path)
			return (MALLOC_ERROR);
		ms->paths[nbr_path] = ft_strjoin(trunc_path, "/");
		trunc_path = ft_free(trunc_path);
		if (!ms->paths[nbr_path])
			return (MALLOC_ERROR);
		if (*full_path)
			full_path++;
		nbr_path++;
	}
	return (SUCCESS);
}

t_error	create_ms_path(t_mini_shell *ms, char *full_path)
{
	int	char_pos;
	int nbr_of_paths;

	char_pos = 0;
	nbr_of_paths = 2;
	while (full_path[char_pos])
	{
		if (full_path[char_pos] == ':')
			nbr_of_paths++;
		char_pos++;
	}
	ms->paths = ft_calloc(nbr_of_paths + 1, sizeof(char *));
	if (!ms->paths)
		return (MALLOC_ERROR);
	ms->paths[nbr_of_paths] = NULL;
	return (SUCCESS);
}

t_error	get_all_paths(t_mini_shell *ms, t_lstd *env_dict)
{
	t_env_arg	*dict_pair;
	char		*paths;

	dict_pair = get_env_dict(env_dict->content);
	while (dict_pair && ft_str_cmp(dict_pair->key, "PATH") != 0)
	{
		env_dict = env_dict->next;
		if (!env_dict)
		{
			ms->paths = NULL;
			return (ERROR);
		}
		dict_pair = get_env_dict(env_dict->content);
	}
	paths = dict_pair->value;
	if (create_ms_path(ms, paths) == MALLOC_ERROR)
		exit_malloc(ms, "get_path: create_ms_path");
	if (fill_paths(ms, paths) == MALLOC_ERROR)
		exit_malloc(ms, "get_path: fill_paths");
	return (SUCCESS);
}

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
	if (!ms->paths || ft_contain(cmd->cmd[0], '/'))
		return (SUCCESS);
	i = -1;
	while (ms->paths[++i])
	{
		cmd->path = ft_strjoin(ms->paths[i], cmd->cmd[0]);
		if (!cmd->path)
			return (MALLOC_ERROR);
		if (access(cmd->path, X_OK) == 0)
			return (SUCCESS);
		cmd->path = ft_free(cmd->path);
	}
	return (SUCCESS);
}