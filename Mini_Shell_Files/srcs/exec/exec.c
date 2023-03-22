/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:39 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 17:59:25 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

void	execve_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	close_all_files(ms);
	if (permission_denied(ms, cmd) == ERROR)
		return ;
	if (!cmd->cmd)
		exit(0);
	if (cmd->is_builtin)
	{
		if (exec_builtin(ms, cmd, TRUE) != MALLOC_ERROR)
			exit(get_exit_code());
		else
			exit_child(ms, cmd, ENOMEM, MALLOC_FAILED);
	}
	else
		execve(cmd->path, cmd->cmd, ms->env);
}

static void	exec_one(t_mini_shell *ms, t_cmd *one)
{
	dup_input(ms, one, "exec_one");
	if (one->is_builtin && !one->need_fork)
	{
		if (exec_builtin(ms, one, FALSE) == MALLOC_ERROR)
			exit_malloc(ms, "execve_cmd");
		return ;
	}
	set_signals(one);
	safe_fork(ms, one, "exec_one");
	if (one->pid)
	{
		if (one->output->fd > 0)
			safe_close(ms, one->output->fd, "exec_one");
		return ;
	}
	if (one->output->fd > 0)
		safe_dup2(ms, one->output->fd, STDOUT_FILENO, "exec_one");
	execve_cmd(ms, one);
}

t_error	exec_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_error	here_doc_status;

	ms->stds[0] = safe_dup(ms, STDIN_FILENO, "exec: exec");
	ms->stds[1] = safe_dup(ms, STDOUT_FILENO, "exec: exec");
	current = ft_lstd_first(ms->cmds);
	here_doc_status = here_docs(ms, current);
	if (here_doc_status == MALLOC_ERROR)
		return (MALLOC_ERROR);
	else if (here_doc_status == ERROR)
	{
		safe_dup2(ms, ms->stds[0], STDIN_FILENO, "exec: exec");
		safe_close(ms, ms->stds[1], "exec: exec");
		return (SUCCESS);
	}
	if (!current->previous && !current->next)
		exec_one(ms, get(current));
	else
		exec_pipeline(ms, current);
	close(STDIN_FILENO);
	wait_exit_status(ms, ms->cmds);
	safe_dup2(ms, ms->stds[0], STDIN_FILENO, "exec: exec");
	safe_dup2(ms, ms->stds[1], STDOUT_FILENO, "exec: exec");
	return (SUCCESS);
}
