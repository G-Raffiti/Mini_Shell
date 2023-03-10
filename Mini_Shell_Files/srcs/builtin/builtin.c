//
// Created by aurel on 2/4/23.
//

#include "../../incs/mini_shell.h"

// TODO : in each builtin set_error_code() !!!
t_error	exec_builtin(t_mini_shell *ms, t_cmd *cmd, t_bool in_pipe)
{
	set_exit_code(0);
	debug (3, "builtin = "YELLOW, cmd->cmd[0], WHITE"\n");
	if (ft_str_cmp(cmd->cmd[0], "export") == 0)
		return (ft_export(ms, cmd, in_pipe));
	else if (ft_str_cmp(cmd->cmd[0], "env") == 0 && ms->env != NULL)
		return (ft_env(ms));
	else if (ft_str_cmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(ms, cmd, in_pipe));
	else if (ft_str_cmp(cmd->cmd[0], "cd") == 0 && !in_pipe)
		return (ft_cd(ms, cmd));
	else if (ft_str_cmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_str_cmp(cmd->cmd[0], "exit") == 0 && !in_pipe)
		return (ft_exit(ms, cmd));
	else if (ft_str_cmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd());
	return (ERROR);
}
