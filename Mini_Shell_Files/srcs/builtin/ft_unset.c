/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:50 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 17:47:59 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ms->env_dict = ft_lstd_first(ft_lstd_remove_and_del(current, \
													(void *)free_dict));
		if (current_sorted)
			ms->env_sort_dict = ft_lstd_first(ft_lstd_remove_and_del \
							(current_sorted, (void *)free_dict));
	}
	if (cmd->cmd[1] && ft_str_cmp(cmd->cmd[1], "PATH") == 0)
		ms->paths = free_split(ms->paths);
	if (fill_env(ms) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (fill_export_env(ms) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	set_exit_code(EXIT_SUCCESS);
	return (SUCCESS);
}
