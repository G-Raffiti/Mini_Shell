//
// Created by rbonneva on 06/02/23.
//

//TODO: cd -> if OLDPWD is not in dict -> bash: cd: OLDPWD not set
// cd - print the OLDPWD and go
#include "../../incs/mini_shell.h"

char	*get_env_value(t_mini_shell *ms, char *key)
{
	t_lstd	*elem;
	t_env_arg *pair;

	elem = ft_lstd_find(ms->env_dict, key, find_in_dict);
	if (!elem)
		return (NULL);
	pair = get_env_dict(elem->content);
	if (!pair)
		return (NULL);
	return (pair->value);
}

void	change_value_in_env(t_mini_shell *ms, char *key, char *value)
{
	(void)ms;
	(void)key;
	(void)value;
	//TODO : set the value in ms->env_dict {key : value} & also in ms->ft_env
	//  'key'='value'
}
// TODO : ~/gjskfjg/fllsjdfk
t_error	ft_cd(t_mini_shell *ms, t_cmd *cmd)
{
	char *path;

	if (cmd->cmd[1] && cmd->cmd[2])
		return (end_child(ms, cmd, 2, "too many arguments\n"));
	if (!cmd->cmd[1] || ft_str_cmp(cmd->cmd[1], "~") == 0)
		path = get_env_value(ms, "HOME");
	else
		path = cmd->cmd[1];
	if (!path)
		return (end_child(ms, cmd, 2, "path parse error\n"));
		//TODO cd: HOME not set
	if (chdir(path) == 0)
		change_value_in_env(ms, "PWD", path);
	return (SUCCESS);
}