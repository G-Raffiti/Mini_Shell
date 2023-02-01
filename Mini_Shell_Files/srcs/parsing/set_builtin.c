//
// Created by rbonneva on 01/02/23.
//

#include "../../incs/mini_shell.h"

void	set_builtin(t_lstd *current)
{
	if (ft_str_cmp(get(current)->cmd[0], "echo") == 0
		|| ft_str_cmp(get(current)->cmd[0], "cd") == 0
		|| ft_str_cmp(get(current)->cmd[0], "pwd") == 0
		|| ft_str_cmp(get(current)->cmd[0], "export") == 0
		|| ft_str_cmp(get(current)->cmd[0], "unset") == 0
		|| ft_str_cmp(get(current)->cmd[0], "env") == 0
		|| ft_str_cmp(get(current)->cmd[0], "exit") == 0)
		get(current)->is_builtin = TRUE;
}