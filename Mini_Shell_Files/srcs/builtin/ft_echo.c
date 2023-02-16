//
// Created by rbonneva on 09/02/23.
//

#include "../../incs/mini_shell.h"

t_bool is_n(char *str)
{
	if (str[0] != '-' && (!str[1] || str[1] != 'n'))
		return (FALSE);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_error	ft_echo(t_mini_shell *ms, t_cmd *cmd)
{
	int		i;
	t_bool	newline;
	char	**split;

	(void) ms;
	i = 0;
	newline = TRUE;
	split = &cmd->cmd[1];
	while (split[i] && is_n(split[i]))
	{
		i++;
		newline = FALSE;
	}
	while (split[i])
	{
		printf("%s", split[i]);
		if (split[i+1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	set_exit_code(0);
	return (SUCCESS);
}