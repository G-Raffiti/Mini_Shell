
#include "../incs/mini_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

void	exit_error(t_mini_shell *mini_shell, int error_code, char *msg)
{
	printf("%sError: %s: %s\n", PROMPT, strerror(error_code), msg);
	free_mini_shell(mini_shell);
	exit(0);
}

t_error	exit_malloc(t_mini_shell *mini_shell)
{
	// TODO : found the global error of the dead "multiple definition of `__odr_asan.g_exit_code';"
	//g_exit_code = ENOMEM;
	printf("Error: %s\n", strerror(ENOMEM));
	free_mini_shell(mini_shell);
	exit(ENOMEM);
}

t_error	exit_end_program(t_mini_shell *mini_shell)
{
	printf("The Program was terminated normally\n");
	free_mini_shell(mini_shell);
	exit(0);
}
