//
// Created by rbonneva on 17/02/23.
//

#include "../../incs/mini_shell.h"

static int count_part_tilde(char *raw)
{
	int		part;
	char	quote;
	int		i;

	part = 1;
	quote = 0;
	i = 0;
	while (raw[i])
	{
		if (set_quote_state(raw[i], &quote) == 0
			&& raw[i] == ' '
			&& (raw[i+1] == '~')
			&& (!raw[i+2] || raw[i+2] == '/' || raw[i+2] == ' '))
			part++;
		i++;
	}
	return (part);
}

static t_error	change_tilde(t_mini_shell *ms, char **split)
{
	int		i;
	t_lstd	*dict;
	char	*tmp;
	char	*tilde;

	i = -1;
	tilde = NULL;
	dict = ft_lstd_find(ms->env_dict, "HOME", find_in_dict);
	if (dict)
		tilde = get_env_dict(dict->content)->value;
	while (tilde && split[++i])
	{
		if (split[i][0] == '~' && !split[i][1])
		{
			split[i] = ft_free(split[i]);
			split[i] = ft_strdup(tilde);
		}
		else if (split[i][0] == '~' && (split[i][1] == '/' || split[i][1] ==
		' '))
		{
			tmp = ft_strjoin(tilde, &split[i][1]);
			split[i] = ft_free(split[i]);
			split[i] = tmp;
		}
		if (!split[i])
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

static t_error	fill_split_tilde(char **split, char *raw)
{
	int		len;
	char	quote;
	int		i;
	int		part;
	char	*start;

	len = 0;
	quote = 0;
	i = -1;
	part = 0;
	start = raw;
	while (raw[++i])
	{
		len++;
		if (!raw[i + 1]
			|| (set_quote_state(raw[i], &quote) == 0
			&& raw[i] == ' '
			&& (raw[i + 1] == '~')
			&& (!raw[i + 2] || raw[i + 2] == '/' || raw[i + 2] == ' ')))
		{
			split[part] = ft_substr(start, 0, len);
			if (split[part] == NULL)
				return (MALLOC_ERROR);
			len = 0;
			part++;
			start = &raw[i + 1];
		}
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
			break;
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
	if (!cmd->raw_cmd)
		return (free_split(split), MALLOC_ERROR);
	return (SUCCESS);
}
