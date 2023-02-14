//
// Created by aurel on 2/5/23.
//

#include "../incs/mini_shell.h"

void	builtin_error_env(char *arg, int error_code, char *msg)
{
	set_exit_code(error_code);
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("‘", 2);
	ft_putendl_fd(msg, 2);
}