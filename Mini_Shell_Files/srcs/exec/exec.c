// Created by Raphael Bonneval on 1/24/23.
//

#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"
#include "debug.h"

static t_error permission_denied(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->input->fd == -1)
	{
		set_exit_code(cmd->input->error);
		if (!cmd->cmd)
			printf("%s: %s\n", cmd->input->name,
					strerror(cmd->input->error));
		else
			printf("%s: %s: %s\n", cmd->cmd[0], cmd->input->name,
					strerror(cmd->input->error));
		safe_close(ms, ms->pipe[1], "exec_first");
		return (ERROR);
	}
	if (cmd->output->fd == -1)
	{
		set_exit_code(cmd->output->error);
		if (!cmd->cmd)
			printf("%s: %s\n", cmd->output->name,
					strerror(cmd->output->error));
		else
			printf("%s: %s: %s\n", cmd->cmd[0], cmd->output->name,
					strerror(cmd->output->error));
		safe_close(ms, ms->pipe[1], "exec_first");
		return (ERROR);
	}
	return (SUCCESS);
}

static void error_exec(t_mini_shell *ms, t_cmd *cmd)
{
	struct stat file_stat;

	if (ft_str_cmp(cmd->cmd[0], ".") == 0)
		exit_child(ms, cmd, 2, FILENAME_REQUIERED);
	stat(cmd->cmd[0], &file_stat);
	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
		exit_child(ms, cmd, 126, IS_DIRECTORY);
	else if ((file_stat.st_mode & S_IFMT) == S_IFREG && access(cmd->cmd[0],
																  X_OK) != 0)
		exit_child(ms, cmd, 126, PERMISSION_DENIED);
	else if (ft_contain(cmd->cmd[0], '/'))
		exit_child(ms, cmd, 127, NO_FILE);
	exit_child(ms, cmd, 127, COMMAND_NOT_FOUND);
}

static void execve_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	t_error exit_status;

	if (!cmd->cmd)
		exit(0);
	if (cmd->is_builtin)
	{
		exit_status = exec_builtin(ms, cmd, TRUE);
		if (exit_status != MALLOC_ERROR)
			exit(get_exit_code());
		else
			exit_malloc(ms, "execve_cmd");
	}
	else
		execve(cmd->path, cmd->cmd, ms->env);
	error_exec(ms, cmd);
}

static void	exec_one(t_mini_shell *ms, t_cmd *one)
{
	t_error exit_status;

	if (permission_denied(ms, one) == ERROR)
		return ;
	if (one->input->fd > 0)
		safe_dup2(ms, one->input->fd, STDIN_FILENO, "exec_one");
	if (one->is_builtin && !one->need_fork)
	{
		exit_status = exec_builtin(ms, one, FALSE);
		if (exit_status == MALLOC_ERROR)
			exit_malloc(ms, "execve_cmd");
		else if (exit_status == ERROR)
			set_exit_code(end_child(ms, one, 127, COMMAND_NOT_FOUND));
		return ;
	}
	set_exec_signals();
	safe_fork(ms, one, "exec_one");
	if (one->pid)
	{
		if (one->output->fd > 0)
			safe_close(ms, one->output->fd, "exec_one");
		return;
	}
	if (one->output->fd > 0)
		safe_dup2(ms, one->output->fd, STDOUT_FILENO, "exec_one");
	execve_cmd(ms, one);
}

static void	exec_first(t_mini_shell *ms, t_cmd *first)
{
	safe_pipe(ms, "exec_first");
	if (permission_denied(ms, first) == ERROR)
		return ;
	if (first->input->fd != -2)
		safe_dup2(ms, first->input->fd, STDIN_FILENO, "exec_first");
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
		safe_dup2(ms, first->output->fd, STDOUT_FILENO, "exec_first");
	execve_cmd(ms, first);
}

static void	exec_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->input->fd == -2)
		safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "exec_mid");
	else if (cmd->input->fd > 0)
		safe_dup2(ms, cmd->input->fd, STDIN_FILENO, "exec_mid");
	safe_pipe(ms, "exec_mid");
	if (permission_denied(ms, cmd) == ERROR)
		return ;
	set_exec_signals();
	safe_fork(ms, cmd, "exec_mid");
	if (cmd->pid)
	{
		if (cmd->output->fd > 0)
			safe_close(ms, cmd->output->fd, "exec_mid");
		safe_close(ms, ms->pipe[1], "exec_mid");
		return ;
	}
	if (cmd->output->fd == -2)
		safe_dup2(ms, ms->pipe[1], STDOUT_FILENO, "exec_mid");
	else
		safe_dup2(ms, cmd->output->fd, STDOUT_FILENO, "exec_mid");
	execve_cmd(ms, cmd);
}

static void	exec_last(t_mini_shell *ms, t_cmd *last)
{
	if (last->input->fd == -2)
		safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "exec_last");
	else if (last->input->fd > 0)
		safe_dup2(ms, last->input->fd, STDIN_FILENO, "exec_last");
	close(ms->pipe[0]);
	if (permission_denied(ms, last) == ERROR)
		return;
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

void	wait_exit_status(t_lstd *current)
{
	int		wstatus;
	int		exit_status;

	exit_status = get_exit_code();
	current = ft_lstd_first(current);
	while (current)
	{
		if (!get(current)->pid)
		{
			current = current->next;
			continue;
		}
		waitpid(get(current)->pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_status = 128 + WTERMSIG(wstatus);
		current = current->next;
	}
	set_exit_code(exit_status);
	if (debug_mod())
		dprintf(2, YELLOW"-▶ %s%d"YELLOW" ◀-"WHITE"\n", get_exit_code() == 0 ?
			GREEN : RED,get_exit_code());
}

t_error	exec_cmds(t_mini_shell *ms)
{
	t_lstd	*current;

	ms->stds[0] = safe_dup(ms, STDIN_FILENO, "exec: exec");
	ms->stds[1] = safe_dup(ms, STDOUT_FILENO, "exec: exec");
	current = ft_lstd_first(ms->cmds);
	if (!current->previous && !current->next)
		exec_one(ms, get(current));
	else
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
	close(STDIN_FILENO);
	wait_exit_status(current);
	safe_dup2(ms, ms->stds[0], STDIN_FILENO, "exec: exec");
	safe_dup2(ms, ms->stds[1], STDOUT_FILENO, "exec: exec");
	return (SUCCESS);
}
