/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:14 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 16:30:40 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

int	check_and_count_prev_h_doc(t_dollar *dlr, int which_function, int
*split_len, int i)
{
	if (which_function == FILL_SPLIT_ARGS)
	{
		if (!(dlr->here_doc[i + 1] && valid_id_dollars(dlr->here_doc[i + 1])))
		{
			dlr->prev_is_arg = 0;
			dlr->len_prev++;
			return (0);
		}
		return (1);
	}
	else if (which_function == SPLIT_COUNT)
	{
		if (i != 0 && dlr->here_doc[i + 1]
			&& valid_id_dollars(dlr->here_doc[i + 1]) && dlr->prev_is_arg == 0)
			*split_len += 2;
		else if (dlr->here_doc[i + 1] && valid_id_dollars(dlr->here_doc[i + 1]))
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

t_error	create_final_raw_h_doc(char **here_doc, int final_len)
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
