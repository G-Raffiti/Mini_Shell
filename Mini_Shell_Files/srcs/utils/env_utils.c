/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:55 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 23:28:24 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	fill_refreshed_env(t_lstd *current, char **str, int which_env)
{
	t_lstd	*content;
	char	*value;
	char	*key;

	content = current->content;
	if (which_env == 0)
		value = ft_strjoin("=", get_env_dict(content)->value);
	else
		value = get_env_dict(content)->value;
	key = get_env_dict(content)->key;
	*str = ft_free(*str);
	*str = ft_strjoin(key, value);
	if (which_env == 0)
		value = ft_free(value);
	if (!*str)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	refresh_env(t_mini_shell *ms)
{
	int	size_dict;

	ms->env = free_split(ms->env);
	size_dict = ft_lstd_size(ms->env_dict);
	ms->env = ft_calloc(size_dict, sizeof(char *));
	if (!ms->env)
		return (MALLOC_ERROR);
	ms->env[size_dict - 1] = NULL;
	return (SUCCESS);
}

t_error	refresh_export_env(t_mini_shell *ms)
{
	int	size_sorted_dict;

	ms->env_sort = free_split(ms->env_sort);
	if (ms->exported)
		size_sorted_dict = ft_lstd_size(ms->env_sort_dict);
	else
		size_sorted_dict = ft_lstd_size(ms->env_dict);
	ms->env_sort = ft_calloc(size_sorted_dict, sizeof(char *));
	if (!ms->env_sort)
		return (MALLOC_ERROR);
	ms->env_sort[size_sorted_dict - 1] = NULL;
	return (SUCCESS);
}

t_error	fill_export_env(t_mini_shell *ms)
{
	t_lstd	*current;
	int		i;

	i = 0;
	refresh_export_env(ms);
	current = ms->env_sort_dict;
	while (current)
	{
		if (ft_str_cmp(get_env_dict(current->content)->key, "_") != 0)
		{
			if (fill_refreshed_env(current, &(ms->env_sort)[i], 1)
				== MALLOC_ERROR)
				return (MALLOC_ERROR);
			i++;
		}
		current = current->next;
	}
	ms->exported = TRUE;
	return (SUCCESS);
}

t_error	fill_env(t_mini_shell *ms)
{
	t_lstd	*current;
	int		i;

	i = 0;
	refresh_env(ms);
	current = ms->env_dict;
	while (current)
	{
		if (fill_refreshed_env(current, &(ms->env)[i], 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		i++;
		current = current->next;
	}
	return (SUCCESS);
}
