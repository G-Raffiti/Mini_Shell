//
// Created by rbonneva on 06/02/23.
//

#include "mini_shell.h"

t_error	ft_pwd(t_mini_shell *ms)
{
	char	cwd[PWD_PATH_SIZE];

	if (getcwd(cwd, PWD_PATH_SIZE))
	{
		ft_putendl_fd(cwd, 1);
		set_exit_code(EXIT_SUCCESS);
		return (SUCCESS);
	}
	ft_putendl_fd(get_env_value(ms, "PWD"), 1);
	return (ERROR);
}
