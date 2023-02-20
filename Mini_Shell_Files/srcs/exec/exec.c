// Created by Raphael Bonneval on 1/24/23.
//

#include <errno.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

void	execve_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	t_error	exit_status;

	if (!cmd->cmd)
		exit(0);
	if (cmd->is_builtin)
	{
		exit_status = exec_builtin(ms, cmd, TRUE);
		if (exit_status != MALLOC_ERROR)
			exit(get_exit_code());
		else
			exit_child(ms, cmd, ENOMEM, MALLOC_FAILED);
	}
	else
		execve(cmd->path, cmd->cmd, ms->env);
	error_exec(ms, cmd);
}

static void	exec_one(t_mini_shell *ms, t_cmd *one)
{
	if (permission_denied(ms, one) == ERROR)
		return ;
	if (one->input->fd > 0)
	{
		safe_dup2(ms, one->input->fd, STDIN_FILENO, "exec_one");
		if (one->input->here_doc_pipe[1])
			close(one->input->here_doc_pipe[1]);
	}
	if (one->is_builtin && !one->need_fork)
	{
		if (exec_builtin(ms, one, FALSE) == MALLOC_ERROR)
			exit_malloc(ms, "execve_cmd");
		return ;
	}
	set_exec_signals();
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

	ms->stds[0] = safe_dup(ms, STDIN_FILENO, "exec: exec");
	ms->stds[1] = safe_dup(ms, STDOUT_FILENO, "exec: exec");
	current = ft_lstd_first(ms->cmds);
	if (here_docs(current) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	else if (get_exit_code() == 130)
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
	if (debug_mod())
		dprintf(2, YELLOW"-▶ %s%d"YELLOW" ◀-"WHITE"\n",
			get_exit_code() == 0 ? GREEN : RED,get_exit_code());
	return (SUCCESS);
}
