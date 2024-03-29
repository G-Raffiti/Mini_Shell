/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:40 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/27 18:42:16 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

int	export_name_is_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=' || !is_not_alpha(arg[i]))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (valid_id_export(arg[i]) == 0)
			return (0);
		i++;
	}
	return (i);
}

t_error	export_in_envs(t_mini_shell *ms, char **extracted)
{
	if (extracted[1][0] == '\0')
	{
		if (!ft_lstd_find(ms->env_sort_dict, extracted[0], find_in_dict_sorted))
		{
			add_in_chosen_env(ms, extracted[0], extracted[2], 3);
			sort_dict(&ms->env_sort_dict, ft_str_cmp);
			if (fill_export_env(ms) == MALLOC_ERROR)
				return (free_split(extracted), MALLOC_ERROR);
		}
	}
	else if (ft_str_cmp(extracted[0], "_") != 0)
	{
		if (add_or_replace_in_chosen_env(ms, extracted[0], extracted[2], 2) \
															== MALLOC_ERROR)
			return (free_split(extracted), MALLOC_ERROR);
		sort_dict(&ms->env_sort_dict, ft_str_cmp);
		if (fill_export_env(ms) == MALLOC_ERROR)
			return (free_split(extracted), MALLOC_ERROR);
	}
	if (ft_str_cmp(extracted[0], "PATH") == 0)
	{
		ms->paths = free_split(ms->paths);
		get_all_paths(ms, ms->env_dict);
	}
	return (free_split(extracted), SUCCESS);
}

t_error	extract_key_value(char *cmd, char ***extracted)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	*extracted = ft_calloc(sizeof(char *), 4);
	if (!*extracted)
		return (MALLOC_ERROR);
	while (++i < 3)
	{
		(*extracted)[i] = ft_calloc(sizeof(char), ft_strlen(cmd) + 1);
		if (!*extracted)
			return (free_split(*extracted), MALLOC_ERROR);
	}
	i = 0;
	while (cmd[++j] && cmd[j] != '=')
		(*extracted)[0][j] = cmd[j];
	if (cmd[j] && cmd[j++] == '=')
		(*extracted)[1][0] = '=';
	while (cmd[j])
		(*extracted)[2][i++] = cmd[j++];
	return (SUCCESS);
}

t_error	ft_export(t_mini_shell *ms, t_cmd *cmd, int in_pipe)
{
	int		i;
	char	**extracted;

	i = 0;
	set_exit_code(EXIT_SUCCESS);
	ms->exported = TRUE;
	if (!cmd->cmd[1])
	{
		display_export(ms);
		return (SUCCESS);
	}
	while (!in_pipe && cmd->cmd[++i])
	{
		if (!export_name_is_valid(cmd->cmd[i]))
			end_child(ms, cmd, 1, INVALID_IDENTIFIER);
		else
		{
			if (extract_key_value(cmd->cmd[i], &extracted) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			if (export_in_envs(ms, extracted) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
	}
	return (SUCCESS);
}
