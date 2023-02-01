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

//void	count_and_next_arg(t_cmd *cmds, int *i, )
t_error	split_count(t_cmd *cmds, int *split_len)
{
	int		i;
	char	quote;
	char	*raw_cmd;
	int 	prev_is_arg;

	i = -1;
	quote = 0;
	prev_is_arg = 0;
	raw_cmd = cmds->raw_cmd;
	while (raw_cmd[++i])
	{
		if (set_quote_state(raw_cmd[i], &quote) != '\'' && raw_cmd[i] == '$')
		{
			if (raw_cmd[i + 1] >= '0' && raw_cmd[i + 1] <= '9')
				continue;
			else if (i != 0 && raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]) && prev_is_arg == 0)
				*split_len += 2;
			else if (raw_cmd[i + 1] && valid_id(raw_cmd[i + 1]))
				*split_len += 1;
			else
				continue;
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
	if (prev_is_arg == 0)
		(*split_len)++;
	if ((*split_len) == 1 && prev_is_arg == 0)
		return (ERROR);
	(*split_len)++;
	dprintf(2, "SPLIT_LEN : %d\n\n", *split_len);
	return (SUCCESS);

}

t_error	replace_dollars(t_mini_shell *ms, t_cmd *cmds)
{

//	char	*raw_cmd;
	char	**splited_raw;
	int		split_len;

	(void)ms;
	split_len  = 0;
	if (!cmds->raw_cmd || split_count(cmds, &split_len) == 0)
		return (SUCCESS);
	splited_raw = ft_calloc(sizeof(char *), split_len);

	if (!splited_raw)
		return (MALLOC_ERROR);


	return(0);


}
