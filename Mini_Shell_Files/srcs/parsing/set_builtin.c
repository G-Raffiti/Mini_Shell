//
// Created by rbonneva on 01/02/23.
//

#include "../../incs/mini_shell.h"

void	set_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return ;
	if (ft_str_cmp(cmd->cmd[0], "echo") == 0
		|| ft_str_cmp(cmd->cmd[0], "cd") == 0
		|| ft_str_cmp(cmd->cmd[0], "pwd") == 0
		|| ft_str_cmp(cmd->cmd[0], "export") == 0
		|| ft_str_cmp(cmd->cmd[0], "unset") == 0
		|| ft_str_cmp(cmd->cmd[0], "env") == 0
		|| ft_str_cmp(cmd->cmd[0], "exit") == 0)
		cmd->is_builtin = TRUE;
	if (ft_str_cmp(cmd->cmd[0], "echo") == 0
		|| ft_str_cmp(cmd->cmd[0], "pwd") == 0
		|| (ft_str_cmp(cmd->cmd[0], "export") == 0 && !cmd->cmd[1])
		//|| ft_str_cmp(cmd->cmd[0], "unset") == 0
		//|| ft_str_cmp(cmd->cmd[0], "env") == 0
		)
		cmd->need_fork = TRUE;
}
