//
// Created by rbonneva on 30/01/23.
//

#include "../../incs/mini_shell.h"

t_error	fill_paths(t_mini_shell *ms, char *full_path)
{
	int		char_pos;
	char	*trunc_path;
	int		start;
	int 	nbr_path;

	char_pos = -1;
	nbr_path = 0;
	while (full_path[++char_pos])
	{
		start = char_pos;
		while (full_path[char_pos] && full_path[char_pos] != ':')
			char_pos++;
		trunc_path = ft_substr(full_path, start, char_pos - start);
		if (!trunc_path)
			return (MALLOC_ERROR);
		ms->paths[nbr_path++] = ft_strjoin(trunc_path, "/");
		if (!ms->paths)
			return (free(trunc_path), MALLOC_ERROR);
	}
	return (SUCCESS);
}

t_error	create_ms_path(t_mini_shell *ms, char *full_path)
{
	int	char_pos;
	int nbr_of_paths;

	char_pos = 0;
	nbr_of_paths = 1;
	while (full_path[char_pos])
	{
		if (full_path[char_pos] != ':')
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
	t_env_arg	*current;

	current = get_env_dict(env_dict);
	while (current && ft_str_cmp(current->key, "PATH") != 0)
	{
		env_dict = env_dict->next;
		current = get_env_dict(env_dict);
	}
	if (create_ms_path(ms, current->value) == MALLOC_ERROR)
		exit_malloc(ms, "get_path: create_ms_path");
	if (fill_paths(ms, current->value) == MALLOC_ERROR)
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
	i = -1;
	if (!ms->paths)
		return (SUCCESS);
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