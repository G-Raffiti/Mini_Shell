//
// Created by rbonneva on 01/02/23.
//

#include "../../incs/mini_shell.h"

void	set_builtin(t_lstd *current)
{
	if (ft_str_cmp(get(current)->cmd[0], "echo")
		|| ft_str_cmp(get(current)->cmd[0], "cd")
		|| ft_str_cmp(get(current)->cmd[0], "pwd")
		|| ft_str_cmp(get(current)->cmd[0], "export")
		|| ft_str_cmp(get(current)->cmd[0], "unset")
		|| ft_str_cmp(get(current)->cmd[0], "env")
		|| ft_str_cmp(get(current)->cmd[0], "exit"))
		get(current)->is_builtin = TRUE;
}