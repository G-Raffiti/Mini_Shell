//
// Created by aurel on 2/9/23.
//

#include "../../incs/mini_shell.h"

t_error	ft_unset(t_mini_shell *ms, t_cmd *cmd, int in_pipe)
{
	t_lstd	*current;
	t_lstd	*current_sorted;
	int		i;

	i = 0;
	while (!in_pipe && cmd->cmd[++i] && ft_str_cmp(cmd->cmd[i], "_") != 0)
	{
		current = ft_lstd_find(ms->env_dict, cmd->cmd[i], find_in_dict);
		current_sorted = ft_lstd_find(ms->env_sort_dict,
				cmd->cmd[i], find_in_dict_sorted);
		if (current)
			ms->env_dict = ft_lstd_first(ft_lstd_remove_and_del(current,
						free_cmd_void));
		if (current_sorted)
			ms->env_sort_dict = ft_lstd_first(ft_lstd_remove_and_del
					(current_sorted, free_cmd_void));
	}
	if (cmd->cmd[1] && ft_str_cmp(cmd->cmd[1], "PATH") == 0)
		ms->paths = free_split(ms->paths);
	fill_env(ms);
	fill_export_env(ms);
	return (SUCCESS);
}
