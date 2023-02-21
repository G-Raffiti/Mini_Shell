//
// Created by rbonneva on 2/20/23.
//

#include <errno.h>
#include "../incs/mini_shell.h"

int	end_child(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg)
{
	int	save_out;

	save_out = safe_dup(ms, STDOUT_FILENO, "exit_child");
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		safe_close(ms, save_out, msg);
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
	set_exit_code(error_code);
	if (!cmd->cmd[1])
		printf("%s: %s\n", cmd->cmd[0], msg);
	else
		printf("%s: %s: %s\n", cmd->cmd[0], cmd->cmd[1], msg);
	safe_dup2(ms, save_out, STDOUT_FILENO, "exec_child");
	return (error_code);
}

int	end_child_arg(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg)
{
	int	save_out;

	save_out = safe_dup(ms, STDOUT_FILENO, "exit_child");
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		safe_close(ms, save_out, msg);
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
	set_exit_code(error_code);
	if (!cmd->cmd[1])
		printf("%s: %s\n", cmd->cmd[0], msg);
	else
		printf("%s: %s: %s\n", cmd->cmd[0], cmd->cmd[1], msg);
	safe_dup2(ms, save_out, STDOUT_FILENO, "exec_child");
	return (error_code);
}
