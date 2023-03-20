/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:33 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:57:33 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

static void	validate_and_replace_tilde(char **split, int i, char *tilde)
{
	char	*tmp;

	if (split[i][0] == '~' && !split[i][1])
	{
		split[i] = ft_free(split[i]);
		split[i] = ft_strdup(tilde);
	}
	else if (split[i][0] == '~' && (split[i][1] == '/'
		|| split[i][1] == ' '))
	{
		tmp = ft_strjoin(tilde, &split[i][1]);
		split[i] = ft_free(split[i]);
		split[i] = tmp;
	}
}

static t_error	change_tilde(t_mini_shell *ms, char **split)
{
	int		i;
	t_lstd	*dict;
	char	*tilde;

	i = -1;
	tilde = NULL;
	dict = ft_lstd_find(ms->env_dict, "HOME", find_in_dict);
	if (dict)
		tilde = get_env_dict(dict->content)->value;
	while (tilde && split[++i])
	{
		validate_and_replace_tilde(split, i, tilde);
		if (!split[i])
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

t_error	replace_tilde(t_mini_shell *ms, t_cmd *cmd)
{
	char	*raw;
	char	**split;

	raw = cmd->raw_cmd;
	while (*raw)
	{
		if (*raw == '~')
			break ;
		raw++;
	}
	if (!*raw)
		return (SUCCESS);
	split = ft_calloc(count_part_tilde(cmd->raw_cmd) + 1, sizeof(char *));
	if (!split)
		return (MALLOC_ERROR);
	if (fill_split_tilde(split, cmd->raw_cmd) == MALLOC_ERROR)
		return (free_split(split), MALLOC_ERROR);
	if (change_tilde(ms, split) == MALLOC_ERROR)
		return (free_split(split), MALLOC_ERROR);
	cmd->raw_cmd = ft_free(cmd->raw_cmd);
	cmd->raw_cmd = ft_strjoin_split(split, "");
	split = free_split(split);
	if (!cmd->raw_cmd)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
