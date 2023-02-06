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
		if (set_quote_state(raw_cmd[i], &quote) != '\'' && raw_cmd[i] == '$' &&
			is_not_alpha(raw_cmd[i + 1]))
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
				if (raw_cmd[i] == '?')
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
	if (debug_mod())
		dprintf(2, "SPLIT_LEN : %d\n\n", *split_len);
	return (SUCCESS);
}

t_error	fill_split_args(t_cmd *cmds, char ***splited_raw)
{
	char	quote;
	char	*raw_cmd;
	int 	prev_is_arg;
	int	i;
	int start_dol;
	int len_prev;
	int nbr;

	i = -1;
	nbr = 0;
	start_dol = 0;
	len_prev = 0;
	quote = 0;
	prev_is_arg = 0;
	raw_cmd = cmds->raw_cmd;

	while (raw_cmd[++i])
	{
		if (set_quote_state(raw_cmd[i], &quote) != '\'' && raw_cmd[i] == '$' &&
			is_not_alpha(raw_cmd[i + 1]))
		{
			start_dol = i;
			if (i != 0 && raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]) && prev_is_arg == 0)
				start_dol = i;
			else if (raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]))
				start_dol = i;
			else
			{
				prev_is_arg = 0;
				len_prev++;
				continue;
			}
			while (raw_cmd[i + 1] && valid_id_dollars(raw_cmd[i + 1]))
			{
				prev_is_arg = 1;

				set_quote_state(raw_cmd[i], &quote);
				i++;
				if (raw_cmd[i] == '?')
					break;
			}
			if (len_prev > 0)
			{
				(*splited_raw)[nbr++] = ft_substr(raw_cmd, start_dol - len_prev, len_prev);
				if ((!*splited_raw))
					return (MALLOC_ERROR);
				if (debug_mod())
					dprintf(2, "Splited[%d] : %s\n",nbr - 1, (*splited_raw)[nbr - 1]);
				len_prev = 0;
			}
			(*splited_raw)[nbr++] = ft_substr(raw_cmd, start_dol, i - start_dol + 1);
			if ((!*splited_raw))
				return (MALLOC_ERROR);
			if (debug_mod())
				dprintf(2, "Splited[%d] : %s\n",nbr - 1, (*splited_raw)[nbr - 1]);

		}
		else
		{
			prev_is_arg = 0;
			len_prev++;
		}
	}
	if (prev_is_arg == 0)
	{
		(*splited_raw)[nbr++] = ft_substr(raw_cmd, ft_strlen(raw_cmd) - len_prev, len_prev);
		if (debug_mod())
			dprintf(2, "Splited[%d] : %s\n",nbr - 1, (*splited_raw)[nbr - 1]);
	}
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
		if (splited_raw[str_pos][c_pos + 1] && (splited_raw)[str_pos][c_pos] == '$' &&
				valid_id_dollars(splited_raw[str_pos][c_pos + 1]))
		{
//			dprintf(2, "raw[%d] BEFORE replaced : %s\n", str_pos, splited_raw[str_pos]);
			key = (&splited_raw[str_pos][c_pos]) + 1;
			get_pair_key_value(ms, dict, &key_value, key);
			if (get_key_and_replace(&splited_raw[str_pos], &key_value, key) == MALLOC_ERROR)
				return (MALLOC_ERROR);
//			dprintf(2, "raw[%d] replaced : %s | len = %ld\n", str_pos, splited_raw[str_pos], ft_strlen(splited_raw[str_pos]));
		}
		else
//			dprintf(2, "raw[%d] NOT replaced : %s | len = %ld\n", str_pos, splited_raw[str_pos], ft_strlen(splited_raw[str_pos]));
		*final_len += ft_strlen(splited_raw[str_pos]);
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

t_error	create_token_and_final_raw(t_cmd **cmd, int final_len)
{

	(*cmd)->is_dollar = ft_calloc(sizeof(t_bool), final_len);
	if (!(*cmd)->is_dollar)
		return (MALLOC_ERROR);
	(*cmd)->raw_cmd = ft_free((*cmd)->raw_cmd);
	(*cmd)->raw_cmd = ft_calloc(sizeof(char), final_len);
	if (!(*cmd)->raw_cmd)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	fill_token(t_cmd *cmds, char **splited_raw, int start_token, int str_pos)
{
	int	i;

	i = -1;
	if (start_token == 0 || start_token == (int)ft_strlen(splited_raw[str_pos - 1]))
	{
		while (cmds->is_dollar[++i])
			cmds->is_dollar[i] = FALSE;
	}
	i = -1;
	while (splited_raw[str_pos][++i])
		cmds->is_dollar[start_token + i] = TRUE;

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

t_error	fill_token_and_final_raw(t_cmd *cmds, char **dup_splited_raw, \
											char **splited_raw)
{
	int			str_pos;
	int 		c_pos;
	int 		start_token;

	str_pos = -1;
	c_pos = 0;
	start_token = 0;
	while (dup_splited_raw[++str_pos])
	{
		if (str_pos != 0)
			start_token += (int)ft_strlen(splited_raw[str_pos]);
		if ((dup_splited_raw)[str_pos][c_pos] == '$' && dup_splited_raw[str_pos][c_pos + 1] && \
            valid_id_dollars(dup_splited_raw[str_pos][c_pos + 1]))
			fill_token(cmds, splited_raw, start_token, str_pos);
	}
	if (fill_final_raw(cmds, splited_raw) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return  (SUCCESS);
}

t_error	replace_dollars(t_mini_shell *ms, t_cmd *cmds)
{
	char	**splited_raw;
	char	**dup_splited_raw;
	int		split_len;
	int		final_len;

	split_len  = 0;
	final_len = 1;
	if (!cmds->raw_cmd || split_count(cmds, &split_len) == 0)
		return (SUCCESS);
	splited_raw = ft_calloc(sizeof(char *), split_len);
	if (!splited_raw)
		return (MALLOC_ERROR);
	if (fill_split_args(cmds, &splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	dup_splited_raw = ft_strtab_dup(splited_raw);
	if (!dup_splited_raw)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (replace_in_split(ms, splited_raw, &final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (create_token_and_final_raw(&cmds, final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (fill_token_and_final_raw(cmds, dup_splited_raw, splited_raw) \
											== MALLOC_ERROR)
		return (free_split(splited_raw), free_split(dup_splited_raw), MALLOC_ERROR);
	debug(3, "RAW_CMD[] == > ", cmds->raw_cmd, "\n");
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
		if (set_quote_state(raw[i], &quote) == 0 && raw[i] == '$' \
					&& (raw[i + 1] == '\'' || raw[i + 1] == '\"'))
		{
			raw[i] = ' ';
		}
	}
	debug(3, "RAW: ", raw, "\n");
}
