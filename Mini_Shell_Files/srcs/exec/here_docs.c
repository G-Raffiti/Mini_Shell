//
// Created by aurel on 2/18/23.
//

#include "../../incs/mini_shell.h"

t_error exec_here_doc(t_cmd *cmd)
{
	char	*buf;

	while ()
}

t_error	here_docs(t_mini_shell *ms, t_lstd *current)
{
	t_cmd	*cmd;
	while (current)
	{
		cmd = get(current);
		if (cmd->input->type == HERE_DOC_REDIR)
		{
			if (exec_here_doc(cmd) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
