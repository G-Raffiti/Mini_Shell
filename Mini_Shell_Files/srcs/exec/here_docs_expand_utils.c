/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_expand_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:27:23 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 17:40:44 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

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
			if (check_and_count_prev_h_doc(&dlr, SPLIT_COUNT, split_len, i)
				== 0)
				continue ;
			check_special_char_h_doc(&dlr.quote, &dlr.prev_is_arg, &i,
				dlr.here_doc);
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
			if (check_and_count_prev_h_doc(&dlr, FILL_SPLIT_ARGS, NULL, i) == 0)
				continue ;
			check_special_char_h_doc(&dlr.quote, &dlr.prev_is_arg, &i,
				dlr.here_doc);
			if (fill_curr_and_prev_h_doc(&dlr, splited_raw, i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			continue ;
		}
		dlr.prev_is_arg = 0;
		dlr.len_prev++;
	}
	if (dlr.prev_is_arg == 0)
		(*splited_raw)[dlr.nbr++] = ft_substr(dlr.here_doc,
				ft_strlen(dlr.here_doc) - dlr.len_prev, dlr.len_prev);
	return (SUCCESS);
}

static t_error	replace_in_split_h_doc(t_mini_shell *ms, char **splited_raw,
					int *final_len)
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
			if (get_key_and_replace_doc(&splited_raw[str_pos], &key_value, key)
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
