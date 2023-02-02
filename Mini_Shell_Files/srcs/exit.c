
#include "../incs/mini_shell.h"
#include "../incs/debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

int		g_exit_code;

void	set_exit_code(int value)
{
	g_exit_code = value;
}

int		get_exit_code(void)
{
	return g_exit_code;
}

void	exit_child(t_cmd *cmd, int error_code, char *msg)
{
	set_exit_code(error_code);
	printf("%d %s: %s\n", g_exit_code, cmd->cmd[0], msg);
	exit(error_code);
}

void	exit_error(t_mini_shell *mini_shell, int error_code, char *msg)
{
	set_exit_code(error_code);
	printf(RED"Error:"WHITE" %s in %s\n", strerror(error_code), msg);
	free_mini_shell(mini_shell);
	exit(error_code);
}

t_error	exit_malloc(t_mini_shell *mini_shell, char *msg)
{
	set_exit_code(ENOMEM);
	printf("Error: %s in %s\n", strerror(ENOMEM), msg);
	free_mini_shell(mini_shell);
	exit(g_exit_code);
}

t_error	exit_end_program(t_mini_shell *mini_shell)
{
	set_exit_code(0);
	printf("exit\n");
	free_mini_shell(mini_shell);
	exit(0);
}
