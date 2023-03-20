/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:59 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:59 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	get_key_env_type(t_env_arg *content)
{
	char	*tmp;

	if (ft_str_cmp(content->key, "_") != 0)
	{
		tmp = ft_strdup(content->key);
		if (!tmp)
			return (MALLOC_ERROR);
		content->key = ft_free(content->key);
		content->key = ft_strjoin("declare -x ", tmp);
		if (!content->key)
			return (MALLOC_ERROR);
		tmp = ft_free(tmp);
	}
	return (SUCCESS);
}

t_error	get_value_env_type(t_env_arg *content)
{
	char	*tmp;

	tmp = ft_strdup(content->value);
	if (!tmp)
		return (MALLOC_ERROR);
	content->value = ft_free(content->value);
	content->value = ft_strjoin("=\"", tmp);
	if (!content->value)
		return (MALLOC_ERROR);
	tmp = ft_free(tmp);
	tmp = ft_strdup(content->value);
	if (!tmp)
		return (MALLOC_ERROR);
	content->value = ft_free(content->value);
	content->value = ft_strjoin(tmp, "\"");
	if (!content->value)
		return (MALLOC_ERROR);
	tmp = ft_free(tmp);
	return (SUCCESS);
}

t_error	get_export_type(t_mini_shell *ms)
{
	t_lstd		*current;
	t_env_arg	*content;

	current = ms->env_sort_dict;
	while (current)
	{
		content = get_env_dict(current->content);
		{
			if (get_key_env_type(content) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			if (get_value_env_type(content) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
