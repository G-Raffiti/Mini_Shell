/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:34 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 20:02:39 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

t_error	permission_denied(t_mini_shell *ms, t_cmd *cmd)
{
	if (cmd->input->fd == -1)
	{
		if (!cmd->cmd)
			printf("%s: %s\n", cmd->input->name,
				strerror(cmd->input->error));
		else
			printf("%s: %s: %s\n", cmd->cmd[0], cmd->input->name,
				strerror(cmd->input->error));
		safe_close(ms, ms->pipe[1], "exec_first");
		set_exit_code(1);
		return (ERROR);
	}
	if (cmd->output->fd == -1)
	{
		if (!cmd->cmd)
			printf("%s: %s\n", cmd->output->name,
				strerror(cmd->output->error));
		else
			printf("%s: %s: %s\n", cmd->cmd[0], cmd->output->name,
				strerror(cmd->output->error));
		safe_close(ms, ms->pipe[1], "exec_first");
		set_exit_code(1);
		return (ERROR);
	}
	return (SUCCESS);
}

void	error_exec(t_mini_shell *ms, t_cmd *cmd)
{
	struct stat	*file_stat;

	file_stat = NULL;
	file_stat = ft_calloc(1, sizeof(struct stat));
	if (!file_stat)
		exit_child(ms, cmd, ENOMEM, MALLOC_FAILED);
	lstat(cmd->cmd[0], file_stat);
	if ((file_stat->st_mode & S_IFMT) == S_IFREG && access(cmd->cmd[0],
			X_OK) != 0)
		return (free(file_stat), exit_child(ms, cmd, 126, PERMISSION_DENIED));
	if (ft_str_cmp(cmd->cmd[0], ".") == 0)
		return (free(file_stat), exit_child(ms, cmd, 2, FILENAME_REQUIERED));
	if (ft_str_cmp(cmd->cmd[0], "..") == 0)
		return (free(file_stat), exit_child(ms, cmd, 127, COMMAND_NOT_FOUND));
	if ((file_stat->st_mode & S_IFMT) == S_IFDIR)
		return (free(file_stat), exit_child(ms, cmd, 126, IS_DIRECTORY));
	if (ft_contain(cmd->cmd[0], '/'))
		return (free(file_stat), exit_child(ms, cmd, 126, NO_FILE));
	return (free(file_stat), exit_child(ms, cmd, 127, COMMAND_NOT_FOUND));
}

void	wait_exit_status(t_mini_shell *ms, t_lstd *current)
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
			continue ;
		}
		waitpid(get(current)->pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_status = 128 + WTERMSIG(wstatus);
		if (exit_status == ENOMEM)
			set_exit_code(ENOMEM);
		current = current->next;
	}
	if (get_exit_code() == ENOMEM)
		exit_malloc(ms, "wait_exit_status");
	set_exit_code(exit_status);
}
