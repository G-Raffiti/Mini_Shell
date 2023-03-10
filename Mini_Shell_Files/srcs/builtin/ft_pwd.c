//
// Created by rbonneva on 06/02/23.
//

#include "mini_shell.h"

t_error	ft_pwd(void)
{
	char	cwd[PWD_PATH_SIZE];

	if (getcwd(cwd, PWD_PATH_SIZE))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	set_exit_code(EXIT_FAILURE);
	return (ERROR);
}
