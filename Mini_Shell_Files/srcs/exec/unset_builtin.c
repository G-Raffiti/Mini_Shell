//
// Created by aurel on 2/9/23.
//

#include "../../incs/mini_shell.h"

t_error	unset(t_mini_shell *ms, t_cmd *cmd, int in_pipe)//TODO : reset path if unset 'PATH'. and unset all builtin
{
	t_lstd	*current;
	t_lstd	*current_sorted;
	int i;

	i = 0;
	while (!in_pipe && cmd->cmd[++i] && ft_str_cmp(cmd->cmd[i], "_") != 0)
	{
		current = ft_lstd_find(ms->env_dict, cmd->cmd[i], find_in_dict);
		current_sorted = ft_lstd_find(ms->env_sort_dict, cmd->cmd[i], find_in_dict_sorted);
		if (current)
			ft_lstd_remove(current);
		if (current_sorted)
			ft_lstd_remove(current_sorted);
	}
	fill_env(ms);
	fill_export_env(ms);
	get_all_paths(ms, ms->env_dict);
	return (SUCCESS);
}