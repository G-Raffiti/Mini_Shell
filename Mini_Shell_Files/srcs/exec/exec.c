//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

void	exec_cmd_child(t_mini_shell *mini_shell, t_lstd *current)
{
	//  TODO [Aurel]: faire comme pipex
	//  Attention aux fd in et out
}

void	make_child(t_mini_shell *ms, t_lstd *current)
{
	safe_fork(ms, current, " exec - make child");
	if (get(current)->pid == 0)
		exec_cmd_child(ms, current);
}

t_error	exec_cmds(t_mini_shell *mini_shell)
{
	t_lstd *current;

	current = mini_shell->cmds;
	while(current)
	{
		if (current->previous && get(current)->input->fd == 0)
		{
			if (mini_shell->pipe[0] != -1
				&& dup2(mini_shell->pipe[0], STDIN_FILENO) == -1)
			{
				exit(0); // TODO [Raffi]: exit status error dup 2
			}
		}
		else if (get(current)->input->fd != 0)
		{
			if (dup2(get(current)->input->fd, STDIN_FILENO) == -1)
			{
				exit(0); //TODO [Raffi]: exit dup2 failed
			}
			close(get(current)->input->fd);
		}
		close(mini_shell->pipe[0]);
		if (current->next && pipe(mini_shell->pipe) == -1)
		{
			exit(0); // TODO [Raffi]: exit Pipe failed
		}
		make_child(mini_shell, current);
		if (current->next)
			close(mini_shell->pipe[1]);
		close(get(current)->output->fd);
		current = current->next;
	}
	/*
	 for_each (t_cmd cmd in mini_shell->cmds)
		if (cmd->infile == 0)
			if (current->previous)
				cmd->infile =
	*/
}

