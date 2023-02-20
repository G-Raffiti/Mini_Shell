//
// Created by aurel on 2/18/23.
//

#include "../../incs/mini_shell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_error exec_here_doc(t_mini_shell *ms, t_cmd *cmd)
{
	char	*line;
	char	*tmp;
	char 	*ret;
	char	*line_read;

	ret = NULL;
	(void)ms;
	set_here_doc_signals();
	while (TRUE)
	{
		line_read = readline("> ");
		if (!line_read || ft_str_cmp(line_read, cmd->input->limiter) == 0 || get_exit_code() == 130)
		{

			if (!ret)
			{
				ret = ft_calloc(sizeof(char), 1);
				if (!ret)
					return (MALLOC_ERROR);
			}
			write(cmd->input->here_doc_pipe[1], ret, ft_strlen(ret));
			ret = ft_free(ret);
			set_interactiv_signals();
			return (SUCCESS);
		}
		line = ft_strjoin(line_read, "\n");
		line_read = ft_free(line_read);
		if (!line)
			return (MALLOC_ERROR);
		tmp = ft_strjoin(ret, line);
		if (!tmp)
			return (MALLOC_ERROR);
		line = ft_free(line);
		ret = ft_free(ret);
		ret = ft_strdup(tmp);
		if (!ret)
			return (MALLOC_ERROR);
		tmp = ft_free(tmp);
	}
	return (ERROR);
}

t_error	here_docs(t_mini_shell *ms, t_lstd *current)
{
	t_cmd	*cmd;
	while (current)
	{
		cmd = get(current);
		if (cmd->input->type == HERE_DOC_REDIR)
		{
			if (exec_here_doc(ms, cmd) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}
