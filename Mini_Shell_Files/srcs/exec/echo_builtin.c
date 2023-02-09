//
// Created by rbonneva on 09/02/23.
//

#include "../../incs/mini_shell.h"

t_error	echo_builtin(t_mini_shell *ms, t_cmd *cmd)
{
	int		i;
	t_bool	newline;
	char	*str;

	(void) ms;
	i = 1;
	newline = TRUE;
	if (cmd->cmd[1] && ft_str_cmp(cmd->cmd[1], "-n"))
	{
		i++;
		newline = FALSE;
	}
	str = ft_strjoin_split(cmd->cmd + i, ' ');
	if (!str)
		return (MALLOC_ERROR);
	if (newline)
		printf("%s\n", str);
	else
		printf("%s", str);
	str = ft_free(str);
	return (SUCCESS);
}