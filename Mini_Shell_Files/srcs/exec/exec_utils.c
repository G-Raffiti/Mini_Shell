/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:36:06 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 17:39:15 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../../incs/mini_shell.h"

void	dup_input(t_mini_shell *ms, t_cmd *cmd, char *msg)
{
	if (cmd->input->fd != -2 && cmd->input->type != HERE_DOC_REDIR)
		safe_dup2(ms, cmd->input->fd, STDIN_FILENO, msg);
	else if (cmd->input->type == HERE_DOC_REDIR)
	{
		safe_dup2(ms, ((t_here_docs *)(ft_lstd_last(cmd->input->here_docs)
					->content))->pipe_h[0], STDIN_FILENO, msg);
		safe_close(ms, ((t_here_docs *)(ft_lstd_last(cmd->input->here_docs)
					->content))->pipe_h[1], msg);
	}
}

void	set_signals(const t_cmd *cmd)
{
	set_exec_signals();
	if (cmd->cmd && ft_str_cmp(cmd->cmd[0], "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	close_parents_fd(t_mini_shell *ms, t_cmd *cmd, char *msg)
{
	safe_close(ms, ms->pipe[1], msg);
	if (cmd->output->fd > 0)
		safe_close(ms, cmd->output->fd, msg);
	if (cmd->input->type == HERE_DOC_REDIR)
		safe_close(ms, ((t_here_docs *)(ft_lstd_last(cmd->input->here_docs)
					->content))->pipe_h[1], msg);
}
