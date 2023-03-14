//
// Created by rbonneva on 06/02/23.
//

#include <string.h>
#include <errno.h>
#include "../../incs/mini_shell.h"

char	*get_env_value(t_mini_shell *ms, char *key)
{
	t_lstd		*elem;
	t_env_arg	*pair;

	elem = ft_lstd_find(ms->env_dict, key, find_in_dict);
	if (!elem)
		return (NULL);
	pair = get_env_dict(elem->content);
	if (!pair)
		return (NULL);
	return (pair->value);
}

t_error	ft_chdir(t_mini_shell *ms, t_cmd *cmd, char *path)
{
	if (!getcwd(NULL, PWD_PATH_SIZE))
		end_child(ms, cmd, EXIT_SUCCESS, NO_PARENT);
	else if (add_or_replace_in_chosen_env(ms, "PWD",
			getcwd(NULL, PWD_PATH_SIZE), 2) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if ((getcwd(NULL, PWD_PATH_SIZE) || path[0] == '/') && chdir(path) == 0)
	{
		if (add_or_replace_in_chosen_env(ms, "OLDPWD", get_env_value(ms, "PWD"),
				2) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (add_or_replace_in_chosen_env(ms, "PWD",
			getcwd(NULL, PWD_PATH_SIZE), 2) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	if (!getcwd(NULL, PWD_PATH_SIZE))
		return (SUCCESS);
	return (end_child_arg(ms, cmd, 1, strerror(errno)));
}

t_error	ft_cd(t_mini_shell *ms, t_cmd *cmd)
{
	char	*path;

	if (cmd->cmd[1] && cmd->cmd[2])
		return (end_child(ms, cmd, 1, TOO_MANY_ARGS));
	if (!cmd->cmd[1] || ft_str_cmp(cmd->cmd[1], "~") == 0)
	{
		path = get_env_value(ms, "HOME");
		if (path == NULL)
			return (end_child(ms, cmd, 1, HOME_NOT_SET));
	}
	else if (ft_str_cmp(cmd->cmd[1], "-") == 0)
	{
		path = get_env_value(ms, "OLDPWD");
		if (path == NULL)
			return (end_child(ms, cmd, 1, OLDPWD_NOT_SET));
		printf("%s\n", get_env_value(ms, "OLDPWD"));
	}
	else
		path = cmd->cmd[1];
	set_exit_code(EXIT_SUCCESS);
	return (ft_chdir(ms, cmd, path));
}
