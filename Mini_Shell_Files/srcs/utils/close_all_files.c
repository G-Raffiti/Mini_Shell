# include "../../incs/mini_shell.h"

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
			close(cmd->input->here_doc_pipe[0]);
			close(cmd->input->here_doc_pipe[1]);
		}
		if (cmd->output->type != PIPE_REDIR && cmd->output->fd > 0)
			close(cmd->output->fd);
		current = current->next;
	}
}