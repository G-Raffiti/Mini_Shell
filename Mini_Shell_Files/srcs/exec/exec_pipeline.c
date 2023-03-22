/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:24 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 18:14:43 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"
#include <signal.h>

static void	exec_first(t_mini_shell *ms, t_cmd *first)
{
	safe_pipe(ms, ms->pipe, "exec_first");
	dup_input(ms, first, "exec_first");
	set_signals(first);
	safe_fork(ms, first, "exec_first");
	if (first->pid)
	{
		safe_close(ms, ms->pipe[1], "exec_first");
		if (first->output->fd > 0)
			safe_close(ms, first->output->fd, "exec_first");
		return ;
	}
	safe_close(ms, ms->pipe[0], "exec first");
	if (first->output->fd == -2)
		safe_dup2(ms, ms->pipe[1], STDOUT_FILENO, "exec_first");
	else
	{
		safe_close(ms, ms->pipe[1], "exec first");
		safe_dup2(ms, first->output->fd, STDOUT_FILENO, "exec_first");
	}
	execve_cmd(ms, first);
}

static void	exec_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->input->fd == -2)
		safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "exec_mid");
	close(ms->pipe[0]);
	dup_input(ms, cmd, "exec_mid");
	safe_pipe(ms, ms->pipe, "exec_mid");
	set_signals(cmd);
	safe_fork(ms, cmd, "exec_mid");
	if (cmd->pid)
	{
		close_parents_fd(ms, cmd, "exec_mid");
		return ;
	}
	if (cmd->output->fd == -2)
		safe_dup2(ms, ms->pipe[1], STDOUT_FILENO, "exec_mid");
	else
	{
		safe_close(ms, ms->pipe[1], "exec_mid");
		safe_dup2(ms, cmd->output->fd, STDOUT_FILENO, "exec_mid");
	}
	execve_cmd(ms, cmd);
}

static void	exec_last(t_mini_shell *ms, t_cmd *last)
{
	if (last->input->fd == -2)
		safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "exec_last");
	dup_input(ms, last, "exec_last");
	close(ms->pipe[0]);
	set_signals(last);
	safe_fork(ms, last, "exec_last");
	if (last->pid)
	{
		if (last->output->fd > 0)
			safe_close(ms, last->output->fd, "exec_last");
		return ;
	}
	if (last->output->fd > 0)
		safe_dup2(ms, last->output->fd, STDOUT_FILENO, "exec_last");
	execve_cmd(ms, last);
}

void	exec_pipeline(t_mini_shell *ms, t_lstd *current)
{
	exec_first(ms, get(current));
	current = current->next;
	while (current && current->next)
	{
		exec_cmd(ms, get(current));
		current = current->next;
	}
	exec_last(ms, get(current));
}
