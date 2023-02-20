#include <errno.h>
#include "../../incs/mini_shell.h"

t_error	parse_error(t_mini_shell *ms, char *msg, int error_code)
{
	int	save_out;

	save_out = safe_dup(ms, STDOUT_FILENO, "exit_child");
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		safe_close(ms, save_out, msg);
		exit_error(ms, errno, msg);
	}
	set_exit_code(error_code);
	printf("%s\n", msg);
	safe_dup2(ms, save_out, STDOUT_FILENO, "exec_child");
	return (ERROR);
}
