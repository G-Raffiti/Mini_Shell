/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:24 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:24 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	safe_pipe(t_mini_shell *ms, int pipes[2], char *msg)
{
	if (pipe((pipes)) == -1)
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

int	safe_dup(t_mini_shell *ms, int std, char *msg)
{
	int	fd;

	fd = dup(std);
	if (fd == -1)
	{
		ms = free_mini_shell(ms);
		exit_error(ms, errno, msg);
	}
	return (fd);
}
