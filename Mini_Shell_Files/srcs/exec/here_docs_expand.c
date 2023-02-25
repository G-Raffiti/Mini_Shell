//
// Created by aucaland on 2/24/23.
//

#include "../../incs/mini_shell.h"

static int	check_id_and_count_prev_h_doc(t_dollar *dlr, int which_function, int
*split_len, int i)
{
	if (which_function == FILL_SPLIT_ARGS)
	{
		if (!(dlr->here_doc[i + 1] && valid_id_dollars
		(dlr->here_doc[i + 1])))
		{
			dlr->prev_is_arg = 0;
			dlr->len_prev++;
			return (0);
		}
		return (1);
	}
	else if (which_function == SPLIT_COUNT)
	{
		if (i != 0 && dlr->here_doc[i + 1] &&
			valid_id_dollars(dlr->here_doc[i + 1]) && dlr->prev_is_arg == 0)
			*split_len += 2;
		else if (dlr->here_doc[i + 1] &&
					valid_id_dollars(dlr->here_doc[i + 1]))
			*split_len += 1;
		else
		{
			dlr->prev_is_arg = 0;
			return (0);
		}
		return (1);
	}
	return (-1);
}

void	check_special_char_h_doc(char *quote, int *prev_is_arg,
						  int *i, char *raw_cmd)
{
	while (raw_cmd[*i + 1] && valid_id_dollars(raw_cmd[*i + 1]))
	{
		*prev_is_arg = 1;
		set_quote_state(raw_cmd[*i], quote);
		(*i)++;
		if ((raw_cmd[*i] == '?' || !is_not_alpha(raw_cmd[*i]))
			&& raw_cmd[*i - 1] == '$')
			return ;
	}
}

static t_error	create_final_raw_h_doc(char **here_doc, int final_len)
{
	*here_doc = ft_free(*here_doc);
	*here_doc = ft_calloc(sizeof(char), final_len);
	if (!*here_doc)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	fill_final_raw_h_doc(char **here_doc, char **splited_raw)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(splited_raw[i]);
	if (!tmp)
		return (MALLOC_ERROR);
	*here_doc = ft_free(*here_doc);
	*here_doc = ft_strdup(tmp);
	if (!*here_doc)
		return (MALLOC_ERROR);
	while (splited_raw[++i])
	{
		*here_doc = ft_free(*here_doc);
		*here_doc = ft_strjoin(tmp, splited_raw[i]);
		if (!*here_doc)
			return (free(tmp), MALLOC_ERROR);
		tmp = ft_free(tmp);
		tmp = ft_strdup(*here_doc);
		if (!tmp)
			return (MALLOC_ERROR);
	}
	free(tmp);
	return (SUCCESS);
}

t_error	fill_end_raw_h_doc(char **here_doc, char **splited_raw)
{
	if (fill_final_raw_h_doc(here_doc, splited_raw) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	split_count_h_doc(char *here_doc, int *split_len)
{
	t_dollar	dlr;
	int			i;

	i = -1;
	initialize_struct_dollar(&dlr, NULL, &here_doc);
	while (dlr.here_doc[++i])
	{
		if (dlr.here_doc[i] == '$')
		{
			if (check_id_and_count_prev_h_doc(&dlr, SPLIT_COUNT, split_len, i)
			== 0)
				continue ;
			check_special_char_h_doc(&dlr.quote, &dlr.prev_is_arg, &i, dlr
			.here_doc);
		}
		else
			dlr.prev_is_arg = 0;
	}
	if (dlr.prev_is_arg == 0)
		(*split_len)++;
	if ((*split_len) == 1 && dlr.prev_is_arg == 0)
		return (ERROR);
	(*split_len)++;
	return (SUCCESS);
}

t_error	fill_curr_and_prev_h_doc(t_dollar *dlr, char ***splited_raw, int i)
{
	if (dlr->len_prev > 0)
	{
		(*splited_raw)[dlr->nbr++] = ft_substr(dlr->here_doc,
											   dlr->start_dol - dlr->len_prev, dlr->len_prev);
		if (!(*splited_raw)[dlr->nbr - 1])
			return (MALLOC_ERROR);
		dlr->len_prev = 0;
	}
	(*splited_raw)[dlr->nbr++] = ft_substr(dlr->here_doc,
										   dlr->start_dol, i - dlr->start_dol + 1);
	if (!(*splited_raw)[dlr->nbr - 1])
		return (MALLOC_ERROR);
	return (SUCCESS);
}

static t_error	fill_split_args_h_doc(char *here_doc, char ***splited_raw)
{
	t_dollar	dlr;
	int			i;

	i = -1;
	initialize_struct_dollar(&dlr, NULL, &here_doc);
	while (dlr.here_doc[++i])
	{
		if (dlr.here_doc[i] == '$')
		{
			dlr.start_dol = i;
			if (check_id_and_count_prev_h_doc(&dlr, FILL_SPLIT_ARGS, NULL, i)
			== 0)
				continue ;
			check_special_char_h_doc(&dlr.quote, &dlr.prev_is_arg, &i, dlr
			.here_doc);
			if (fill_curr_and_prev_h_doc(&dlr, splited_raw, i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			continue ;
		}
		dlr.prev_is_arg = 0;
		dlr.len_prev++;
	}
	if (dlr.prev_is_arg == 0)
		(*splited_raw)[dlr.nbr++] = ft_substr(dlr.here_doc,
											  ft_strlen(dlr.here_doc) - dlr
											  .len_prev, dlr.len_prev);
	return (SUCCESS);
}

static t_error	replace_in_split_h_doc(t_mini_shell *ms, char **splited_raw,
										 int
*final_len)
{
	t_lstd		*dict;
	t_env_arg	*key_value;
	char		*key;
	int			str_pos;
	int			c_pos;

	dict = NULL;
	key_value = NULL;
	str_pos = -1;
	c_pos = 0;
	while (splited_raw[++str_pos])
	{
		if (splited_raw[str_pos][c_pos] && splited_raw[str_pos][c_pos + 1]
			&& (splited_raw)[str_pos][c_pos] == '$' &&
			valid_id_dollars(splited_raw[str_pos][c_pos + 1]))
		{
			key = (&splited_raw[str_pos][c_pos]) + 1;
			get_pair_key_value(ms, dict, &key_value, key);
			if (get_key_and_replace(&splited_raw[str_pos], &key_value, key)
				== MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		*final_len += (int)ft_strlen(splited_raw[str_pos]);
	}
	return (SUCCESS);
}

t_error	expand_here_doc(t_mini_shell *ms, char **here_doc, t_here_docs *here)
{
	char	**splited_raw;
	int		split_len;
	int		final_len;

	final_len = 1;
	split_len = 0;
	if (!*here_doc || !here->have_to_expand || \
				split_count_h_doc(*here_doc, &split_len) == 0)
		return (SUCCESS);
	splited_raw = ft_calloc(sizeof(char *), split_len);
	if (!splited_raw)
		return (MALLOC_ERROR);
	if (fill_split_args_h_doc(*here_doc, &splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (replace_in_split_h_doc(ms, splited_raw, &final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (create_final_raw_h_doc(here_doc, final_len) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	if (fill_end_raw_h_doc(here_doc, splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
	splited_raw = free_split(splited_raw);
	return (SUCCESS);
}