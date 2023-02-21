#include "../../incs/mini_shell.h"

int	check_id_and_count_prev(t_dollar *dlr, char *which_function, int
	*split_len, int i)
{
	if (ft_str_cmp(which_function, FILL_SPLIT_ARGS) == 0)
	{
		if (!(dlr->raw_cmd[i + 1] && valid_id_dollars(dlr->raw_cmd[i + 1])))
		{
			dlr->prev_is_arg = 0;
			dlr->len_prev++;
			return (0);
		}
		return (1);
	}
	else if (ft_str_cmp(which_function, SPLIT_COUNT) == 0)
	{
		if (i != 0 && dlr->raw_cmd[i + 1]
			&& valid_id_dollars(dlr->raw_cmd[i + 1]) && dlr->prev_is_arg == 0)
			*split_len += 2;
		else if (dlr->raw_cmd[i + 1] && valid_id_dollars(dlr->raw_cmd[i + 1]))
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

void	check_secial_char(char *quote, int *prev_is_arg,
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

void	replace_dollar_before_quotes(t_cmd *cmd)
{
	int		i;
	char	quote;
	char	*raw;

	i = -1;
	quote = 0;
	raw = cmd->raw_cmd;
	while (raw[++i])
	{
		if (set_quote_state(raw[i], &quote) != '\'' && raw[i] == '$'
			&& (raw[i + 1] == '\'' || raw[i + 1] == '\"'))
			raw[i] = ' ';
	}
}
