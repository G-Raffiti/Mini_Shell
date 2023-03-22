/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:11 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 15:33:10 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

void	close_all_files(t_mini_shell *ms)
{
	t_lstd	*current;
	t_cmd	*cmd;

	close(ms->stds[0]);
	close(ms->stds[1]);
	current = ft_lstd_first(ms->cmds);
	while (current)
	{
		cmd = get(current);
		if (cmd->input->type != PIPE_REDIR
			&& cmd->input->type != HERE_DOC_REDIR
			&& cmd->input->fd > 0)
			close(cmd->input->fd);
		else if (cmd->input->type == HERE_DOC_REDIR && cmd->input->fd > 0)
		{
			close(((t_here_docs *)(ft_lstd_last(cmd->input->here_docs)
						->content))->pipe_h[0]);
			close(((t_here_docs *)(ft_lstd_last(cmd->input->here_docs)
						->content))->pipe_h[1]);
		}
		if (cmd->output->type != PIPE_REDIR && cmd->output->fd > 0)
			close(cmd->output->fd);
		//TODO: check pipe 0 or pipe 1 to close. (check for here doc)
		current = current->next;
	}
}
