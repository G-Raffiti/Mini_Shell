//
// Created by Raphael Bonneval on 29/01/2023.
//

#include <errno.h>
#include "../../incs/mini_shell.h"

void	safe_fork(t_mini_shell *ms, t_cmd *cmd, char *msg)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
}

void	safe_pipe(t_mini_shell *ms, char *msg)
{
	if (pipe((ms->pipe)) == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
}

void	safe_close(t_mini_shell *ms, int fd, char *msg)
{
	if (close(fd) == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
}

void	safe_dup2(t_mini_shell *ms, int fd, int std, char *msg)
{
	if (dup2(fd, std) == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
	safe_close(ms, fd, msg);
}

void	safe_rev_dup2(t_mini_shell *ms, int std, int fd, char *msg)
{
	if (dup2(std, fd) == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
	safe_close(ms, fd, msg);
}