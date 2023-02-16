
#include "../incs/mini_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

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
	printf("%s: %s\n", cmd->cmd[0], msg);
	safe_dup2(ms, save_out, STDOUT_FILENO, "exec_child");
	return(error_code);
}

void	exit_child(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg)
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
	printf("%s: %s\n", cmd->cmd[0], msg);
	safe_dup2(ms, save_out, STDOUT_FILENO, "exec_child");
	exit(error_code);
}

void	exit_error(t_mini_shell *ms, int error_code, char *msg)
{
	set_exit_code(error_code);
	printf(RED"Error:"WHITE" %s in %s\n", strerror(error_code), msg);
	free_mini_shell(ms);
	exit(error_code);
}

t_error	exit_malloc(t_mini_shell *mini_shell, char *msg)
{
	set_exit_code(ENOMEM);
	printf(RED"Error:"WHITE" %s in %s\n", strerror(ENOMEM), msg);
	free_mini_shell(mini_shell);
	exit(get_exit_code());
}

t_error	exit_end_program(t_mini_shell *ms)
{
	set_exit_code(0);
	printf("exit\n");
	free_mini_shell(ms);
	exit(0);
}
