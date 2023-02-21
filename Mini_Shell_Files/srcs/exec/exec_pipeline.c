#include "../../incs/mini_shell.h"

static void	exec_first(t_mini_shell *ms, t_cmd *first)
{
	safe_pipe(ms, ms->pipe, "exec_first");
	if (permission_denied(ms, first) == ERROR)
		return ;
	if (first->input->fd != -2)
	{
		safe_dup2(ms, first->input->fd, STDIN_FILENO, "exec_first");
		if (first->input->here_doc_pipe[1])
			close(first->input->here_doc_pipe[1]);
	}
	set_exec_signals();
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
	else
		close(ms->pipe[0]);
	if (cmd->input->fd > 0)
	{
		safe_dup2(ms, cmd->input->fd, STDIN_FILENO, "exec_mid");
		if (cmd->input->here_doc_pipe[1])
			close(cmd->input->here_doc_pipe[1]);
	}
	safe_pipe(ms, ms->pipe, "exec_mid");
	if (permission_denied(ms, cmd) == ERROR)
		return ;
	set_exec_signals();
	safe_fork(ms, cmd, "exec_mid");
	if (cmd->pid)
	{
		safe_close(ms, ms->pipe[1], "exec_mid");
		if (cmd->output->fd > 0)
			safe_close(ms, cmd->output->fd, "exec_mid");
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
	else
		close(ms->pipe[0]);
	if (last->input->fd > 0)
	{
		safe_dup2(ms, last->input->fd, STDIN_FILENO, "exec_last");
		if (last->input->here_doc_pipe[1])
			close(last->input->here_doc_pipe[1]);
	}
	close(ms->pipe[0]);
	if (permission_denied(ms, last) == ERROR)
		return ;
	set_exec_signals();
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
