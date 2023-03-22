/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:18 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 19:36:45 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	exec_builtin(t_mini_shell *ms, t_cmd *cmd, t_bool in_pipe)
{
	if (ft_str_cmp(cmd->cmd[0], "export") == 0)
		return (ft_export(ms, cmd, in_pipe));
	else if (ft_str_cmp(cmd->cmd[0], "env") == 0 && ms->env != NULL)
		return (ft_env(ms));
	else if (ft_str_cmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(ms, cmd, in_pipe));
	else if (ft_str_cmp(cmd->cmd[0], "cd") == 0 && !in_pipe)
		return (ft_cd(ms, cmd));
	else if (ft_str_cmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_str_cmp(cmd->cmd[0], "exit") == 0 && !in_pipe)
		return (ft_exit(ms, cmd));
	else if (ft_str_cmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd(ms));
	return (ERROR);
}
