//
// Created by aurel on 2/1/23.
//

#include "../../incs/mini_shell.h"

t_error	split_count(t_cmd *cmds, int *split_len)
{
	char	quote;
	char	*raw_cmd;
	int 	prev_is_arg;
	int	i;

	i = -1;
	quote = 0;
	prev_is_arg = 0;
	raw_cmd = cmds->raw_cmd;

	while (raw_cmd[++i])
	{
		if (set_quote_state(raw_cmd[i], &quote) != '\'' && raw_cmd[i] == '$')
		{
			if (i != 0 && raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]) && prev_is_arg == 0)
				*split_len += 2;
			else if (raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]))
				*split_len += 1;
			else
			{
				prev_is_arg = 0;
				continue;
			}
			while (raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]))
			{
				prev_is_arg = 1;
				set_quote_state(raw_cmd[i], &quote);
				i++;
				if ((raw_cmd[i] == '?' || !is_not_alpha(raw_cmd[i])) && raw_cmd[i - 1] == '$')
					break;
			}
		}
		else
			prev_is_arg = 0;
	}
//	count_arg(raw_cmd, split_len, &prev_is_arg, quote);//TODO : REFACTO 40 LIGNEEEEEE
	if (prev_is_arg == 0)
		(*split_len)++;
	if ((*split_len) == 1 && prev_is_arg == 0)
		return (ERROR);
	(*split_len)++;
	return (SUCCESS);
}

void	check_quote_and_special_arg_treatment(char *quote, int *prev_is_arg, int
*i, char *raw_cmd)
{
	while (raw_cmd[*i + 1] && valid_id_dollars(raw_cmd[*i + 1]))
	{
		*prev_is_arg = 1;
		set_quote_state(raw_cmd[*i], quote);
		(*i)++;
		if ((raw_cmd[*i] == '?' || !is_not_alpha(raw_cmd[*i])) && raw_cmd[*i -
		1] == '$')
			return ;
	}
}

t_error	fill_curr_and_prev(t_dollar *dlr, char ***splited_raw, int i)
{
	if (dlr->len_prev > 0)
	{
		(*splited_raw)[dlr->nbr++] = ft_substr(dlr->raw_cmd, dlr->start_dol -
		dlr->len_prev, dlr->len_prev);
		if (!(*splited_raw)[dlr->nbr - 1])
			return (MALLOC_ERROR);
		dlr->len_prev = 0;
	}
	(*splited_raw)[dlr->nbr++] = ft_substr(dlr->raw_cmd, dlr->start_dol, i -
	dlr->start_dol + 1);
	if (!(splited_raw)[dlr->nbr - 1])
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	check_id_and_count_prev(t_dollar *dlr, int i)
{
	if (!(dlr->raw_cmd[i + 1] && valid_id_dollars(dlr->raw_cmd[i + 1])))
	{
		dlr->prev_is_arg = 0;
		dlr->len_prev++;
		return (0);
	}
	return (1);
}

t_error	fill_split_args(t_cmd *cmds, char ***splited_raw)
{
	t_dollar	dlr;
	int			i;

	i = -1;
	initialize_struct_dollar(&dlr, cmds);
	while (dlr.raw_cmd[++i])
	{
		if (set_quote_state(dlr.raw_cmd[i], &dlr.quote) != '\'' && dlr.raw_cmd[i] == '$')
		{
			dlr.start_dol = i;
			if (check_id_and_count_prev(&dlr, i) == 0)
				continue;
			check_quote_and_special_arg_treatment(&dlr.quote, &dlr.prev_is_arg, &i,
												  dlr.raw_cmd);
			if (fill_curr_and_prev(&dlr, splited_raw, i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			continue ;
		}
		dlr.prev_is_arg = 0;
		dlr.len_prev++;
	}
	if (dlr.prev_is_arg == 0)
		(*splited_raw)[dlr.nbr++] = ft_substr(dlr.raw_cmd, ft_strlen(dlr.raw_cmd) - dlr.len_prev, dlr.len_prev);
	return (SUCCESS);
}

void	get_pair_key_value(t_mini_shell  *ms, t_lstd *dict, t_env_arg **key_value, char *key)
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

t_error	replace_in_split(t_mini_shell *ms, char **splited_raw, int *final_len)
{
	t_lstd		*dict;
	t_env_arg	*key_value;
	char		*key;
	int			str_pos;
	int 		c_pos;

	dict = NULL;
	key_value = NULL;
	str_pos = -1;
	c_pos = 0;
	while (splited_raw[++str_pos])
	{
		if (splited_raw[str_pos][c_pos] && splited_raw[str_pos][c_pos + 1] && (splited_raw)[str_pos][c_pos] == '$' &&
			valid_id_dollars(splited_raw[str_pos][c_pos + 1]))
		{
			key = (&splited_raw[str_pos][c_pos]) + 1;
			get_pair_key_value(ms, dict, &key_value, key);
			if (get_key_and_replace(&splited_raw[str_pos], &key_value, key) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		*final_len += (int)ft_strlen(splited_raw[str_pos]);
	}
	return  (SUCCESS);
}

char	**ft_strtab_dup(char **tab_to_dup)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_calloc(sizeof(char *), ft_strlen_tab(tab_to_dup) + 1);
	if (!tab)
		return (NULL);
	while (tab_to_dup[++i])
	{
		tab[i] = ft_strdup(tab_to_dup[i]);
		if (!tab[i])
			return (free_split(tab), NULL);
	}
	return (tab);
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
	char 	*tmp;

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
	return  (SUCCESS);
}

t_error	replace_dollars(t_mini_shell *ms, t_cmd *cmds)
{
	char	**splited_raw;
	int		split_len;
	int		final_len;

	final_len = 1;
	split_len = 0;
	if (!cmds->raw_cmd || split_count(cmds, &split_len) == 0)
		return (SUCCESS);
	splited_raw = ft_calloc(sizeof(char *), split_len);
	if (!splited_raw)
		return (MALLOC_ERROR);
	if (fill_split_args(cmds, &splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (replace_in_split(ms, splited_raw, &final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (create_final_raw(&cmds, final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (fill_end_raw(cmds, splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	splited_raw = free_split(splited_raw);
	return(0);
}

void	replace_dollar_before_quotes(t_cmd *cmd)
{
	int		i;
	char 	quote;
	char 	*raw;

	i = -1;
	quote = 0;
	raw = cmd->raw_cmd;
	while (raw[++i])
	{
		if (set_quote_state(raw[i], &quote) != '\'' && raw[i] == '$' \
					&& (raw[i + 1] == '\'' || raw[i + 1] == '\"'))
			raw[i] = ' ';
	}
}
