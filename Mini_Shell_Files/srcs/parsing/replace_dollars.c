//
// Created by aurel on 2/1/23.
//

#include "../../incs/mini_shell.h"

int 	valid_id(char c)
{
	if (ft_contain(INV_ID, c) || c >= 127 || c == ' ')
		return (0);
	return (1);
}

int	is_not_alpha(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

//void	count_arg(char *raw_cmd, int *split_len, int *prev_is_arg, char quote)
//{
//
//
//}

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
			if (i != 0 && raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]) && prev_is_arg == 0)
				*split_len += 2;
			else if (raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]))
				*split_len += 1;
			else
			{
				prev_is_arg = 0;
				continue;
			}
			while (raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]))
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
			if (i != 0 && raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]) && prev_is_arg == 0)
				start_dol = i;
			else if (raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]))
				start_dol = i;
			else
			{
				prev_is_arg = 0;
				len_prev++;
				continue;
			}
			while (raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]))
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
				dprintf(2, "%s\n", (*splited_raw)[nbr - 1]);
				len_prev = 0;
			}
			(*splited_raw)[nbr++] = ft_substr(raw_cmd, start_dol, i - start_dol + 1);
			if ((!*splited_raw))
				return (MALLOC_ERROR);
			dprintf(2, "%s\n", (*splited_raw)[nbr - 1]);

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
		dprintf(2, "%s\n", (*splited_raw)[nbr - 1]);
	}
	return (SUCCESS);
}

//t_error	create_final_raw(cahr ***splited_raw, int *final_len)
//{
//	i = 0;
//	while (splited_raw[i])
//	{
//		if ()
//	}
//}

t_error	replace_dollars(t_mini_shell *ms, t_cmd *cmds)
{

//	char	*raw_cmd;
	char	**splited_raw;
	int		split_len;
//	int		final_len;

	(void)ms;
	split_len  = 0;
//	final_len = 0;
	if (!cmds->raw_cmd || split_count(cmds, &split_len) == 0)
		return (SUCCESS);
	splited_raw = ft_calloc(sizeof(char *), split_len);
	if (!splited_raw)
		return (MALLOC_ERROR);
	if (fill_split_args(cmds, &splited_raw) == MALLOC_ERROR)
		return (free_split(splited_raw), MALLOC_ERROR);
//	if (create_final_raw(splited_raw, &final_len) == MALLOC_ERROR)
//		return (MALLOC_ERROR);

	exit(0);
	return(0);
}
