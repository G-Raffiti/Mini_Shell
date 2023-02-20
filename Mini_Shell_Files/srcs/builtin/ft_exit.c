//
// Created by rbonneva on 16/02/23.
//

#include "../../incs/mini_shell.h"

t_error	ft_exit(t_mini_shell *ms, t_cmd *cmd)
{
	int		code;
	char	*str;

	str = cmd->cmd[1];
	if (str
		&& (!ft_is_digit_signed(str)
			|| !ft_isdigit(str + 1)
			|| (str[0] != '-' && ft_str_cmp(str, "9223372036854775807") > 0)
			|| (str[0] == '-' && ft_str_cmp(str, "-9223372036854775808") > 0)))
	{
		end_child(ms, cmd, 2, NUMERIC_ARGS);
		code = 2;
	}
	else if (ft_strlen_tab(cmd->cmd) > 2)
	{
		printf ("exit\n");
		return (end_child(ms, cmd, EXIT_FAILURE, TOO_MANY_ARGS));
	}
	else if (str)
		code = ft_atoi(str);
	else
		code = EXIT_SUCCESS;
	set_exit_code(code);
	return (exit_end_program(ms, get_exit_code()));
}
