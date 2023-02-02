//
// Created by Raphael Bonneval on 1/24/23.
//
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

//t_error	pipe_cmd_fd(t_mini_shell *ms, t_cmd *cmd, int is_first)
//{
////	if (cmd->input->fd == -1)
////	{
////		perror(cmd->input->name);
////		safe_close(ms, ms->pipe[1], "exec: pipe_cmd_fd");
////		return (ERROR);
////	}
//
//	return (SUCCESS);
//}

//void	make_child(t_mini_shell *ms, t_cmd *cmd)
//{
//	if (cmd->output->fd == -1)
//	{
//		perror(cmd->output->name);
//		safe_close(ms, ms->pipe[1], "exec: pipe_cmd_fd 1");
//		return ;
//	}

//}

//void	exec_cmd(t_mini_shell *ms, t_cmd *cmd)
//{
//
//}

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
	close(ms->pipe[1]);
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

		if (cmd->input->fd == -2)
			cmd->input->fd = ms->pipe_retour[0];
		safe_dup2(ms, cmd->input->fd, ms->pipe[1], "DUP input->pipe[1]");
		if (cmd->input->fd != ms->pipe_retour[0])
			safe_close(ms, ms->pipe_retour[0], "CLOSE piperetour[0]");
		safe_pipe(ms, "Pipe");
		safe_fork(ms, cmd, "FORK");
		if (!cmd->pid)
		{
			safe_dup2(ms, ms->pipe[0], STDIN_FILENO, "DUP PIPE[0]->STDIN");
			if (cmd->output->fd != -2)
				safe_dup2(ms ,cmd->output->fd , STDOUT_FILENO, "DUP "
																  "output->STDOUT");
			else if (current->next)
				safe_dup2(ms , ms->pipe_retour[1], STDOUT_FILENO, "DUP "
															  "PIPE_R[1]->STDOUT");
			debug_fd(ms, cmd);
			execve(cmd->path, cmd->cmd, ms->env);
			exit_child(cmd, 127, "command not found");
		}
		dprintf(2, "DEBUG\n");
		current = current->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	dprintf(2, "exec end");
	return (SUCCESS);
}

