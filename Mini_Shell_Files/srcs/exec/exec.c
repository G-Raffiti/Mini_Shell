// Created by Raphael Bonneval on 1/24/23.
//

#include <errno.h>
#include <signal.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

void	execve_cmd(t_mini_shell *ms, t_cmd *cmd)
{
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
	error_exec(ms, cmd);
}

static void	exec_one(t_mini_shell *ms, t_cmd *one)
{
	if (permission_denied(ms, one) == ERROR)
		return ;
	if (one->input->fd > 0 && one->input->type != HERE_DOC_REDIR)
		safe_dup2(ms, one->input->fd, STDIN_FILENO, "exec_one");
	else if (one->input->type == HERE_DOC_REDIR)
	{
		safe_dup2(ms, ((t_here_docs *)(ft_lstd_last(one->input->here_docs)
				->content))->pipe_h[0], STDIN_FILENO, "exec_one");
		safe_close(ms,((t_here_docs *)(ft_lstd_last(one->input->here_docs)
				->content))->pipe_h[1], "exec_one");
	}
	if (one->is_builtin && !one->need_fork)
	{
		if (exec_builtin(ms, one, FALSE) == MALLOC_ERROR)
			exit_malloc(ms, "execve_cmd");
		return ;
	}
	set_exec_signals();
	if (one->cmd && ft_str_cmp(one->cmd[0], "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
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
	if (here_docs(ms, current) == MALLOC_ERROR)
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
	return (SUCCESS);
}
