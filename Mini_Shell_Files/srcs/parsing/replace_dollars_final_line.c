/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_final_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:41 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:57:41 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

void	get_pair_key_value(t_mini_shell *ms, t_lstd *dict,
			t_env_arg **key_value, char *key)
{
	dict = ft_lstd_find(ms->env_dict, key, find_in_dict);
	if (dict)
		*key_value = get_env_dict(dict->content);
	else
		*key_value = NULL;
}

t_error	get_key_and_replace(char **raw, t_env_arg **key_value, char *key)
{
	if (ft_str_cmp(key, "?") == 0)
	{
		*raw = ft_free(*raw);
		*raw = ft_itoa(get_exit_code());
		if (!*raw)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	*raw = ft_free(*raw);
	if (*key_value)
	{
		*raw = ft_strdup((*key_value)->value);
		if (!*raw)
			return (MALLOC_ERROR);
	}
	else
	{
		*raw = ft_calloc(sizeof(char), 1);
		if (!*raw)
			return (MALLOC_ERROR);
		(*raw)[0] = '\0';
	}
	return (SUCCESS);
}

t_error	create_final_raw(t_cmd **cmd, int final_len)
{
	(*cmd)->raw_cmd = ft_free((*cmd)->raw_cmd);
	(*cmd)->raw_cmd = ft_calloc(sizeof(char), final_len);
	if (!(*cmd)->raw_cmd)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	fill_final_raw(t_cmd *cmds, char **splited_raw)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(splited_raw[i]);
	if (!tmp)
		return (MALLOC_ERROR);
	cmds->raw_cmd = ft_free(cmds->raw_cmd);
	cmds->raw_cmd = ft_strdup(tmp);
	if (!cmds->raw_cmd)
		return (MALLOC_ERROR);
	while (splited_raw[++i])
	{
		cmds->raw_cmd = ft_free(cmds->raw_cmd);
		cmds->raw_cmd = ft_strjoin(tmp, splited_raw[i]);
		if (!cmds->raw_cmd)
			return (free(tmp), MALLOC_ERROR);
		tmp = ft_free(tmp);
		tmp = ft_strdup(cmds->raw_cmd);
		if (!tmp)
			return (MALLOC_ERROR);
	}
	free(tmp);
	return (SUCCESS);
}

t_error	fill_end_raw(t_cmd *cmds, char **splited_raw)
{
	if (fill_final_raw(cmds, splited_raw) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
