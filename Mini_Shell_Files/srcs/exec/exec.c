//
// Created by Raphael Bonneval on 1/24/23.
//

#include <sys/wait.h>
#include <errno.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

t_error	pipe_cmd_fd(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->input->fd == -1)
	{
		perror(cmd->input->name);
		safe_close(ms, ms->pipe[1], "exec: pipe_cmd_fd");
		return (ERROR);
	}
	if (cmd->input->fd == -2)
		cmd->input->fd = ms->pipe[0];
	safe_dup2(ms, cmd->input->fd, STDIN_FILENO, "exec: pipe_cmd_fd");
	if (cmd->input->fd != ms->pipe[0])
		safe_close(ms, ms->pipe[0], "exec: pipe_cmd_fd");
	safe_pipe(ms, "exec: pipe_cmd_fd");
	return (SUCCESS);
}

void	make_child(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->output->fd == -1)
	{
		perror(cmd->output->name);
		safe_close(ms, ms->pipe[1], "exec: pipe_cmd_fd 1");
		return ;
	}
	if (cmd->output->fd == -2)
		cmd->output->fd = ms->pipe[1];
	safe_fork(ms, cmd, "exec: make_child 2");
	if (cmd->pid)
	{
		if (cmd->output->fd != ms->pipe[1])
			safe_close(ms, ms->pipe[1], "exec: make_child 3");
		//safe_close(ms, cmd->output->fd, "exec: make_child 4");
	}
	debug_fd(ms, cmd);
	safe_dup2(ms, cmd->output->fd, STDOUT_FILENO, "exec: make_child 5");
	close(ms->pipe[1]);
}

void	exec_cmd(t_mini_shell *ms, t_cmd *cmd)
{
	execve(cmd->path, cmd->cmd, ms->env);
	exit_child(cmd, 127, "command not found");
}

void	close_pipeline(t_mini_shell *ms)
{
	char	**cmd;
	int		pid;

	cmd = (char *[2]){"/usr/bin/cat", NULL};
	safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "exec: close_pipeline 1");
	pid = fork();
	if (pid == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, "last_fork");
	}
	close(ms->)
	execve(cmd[0], cmd, ms->env);
	exit(0);
}

t_error	exec_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_cmd	*cmd;

	current = ft_lstd_first(ms->cmds);
	safe_pipe(ms, "exec: exec_cmds");
	while (current)
	{
		cmd = get(current);
		if (pipe_cmd_fd(ms, cmd) == ERROR)
		{
			current = current->next;
			continue;
		}
		make_child(ms, cmd);
		dprintf(1, "PID=%d", cmd->pid);
		if (!cmd->pid)
			exec_cmd(ms, cmd);
		current = current->next;
	}
	close_pipeline(ms);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (SUCCESS);
}

