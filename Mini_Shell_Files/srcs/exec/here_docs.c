//
// Created by aurel on 2/18/23.
//

#include "../../incs/mini_shell.h"
#include <readline/readline.h>

static char	*join_lines(char **line_read, char **ret)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(*line_read, "\n");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(*ret, tmp);
	if (!line)
		return (free(tmp), NULL);
	tmp = ft_free(tmp);
	*line_read = ft_free(*line_read);
	*ret = ft_free(*ret);
	return (line);
}

static t_error	exec_here_doc(t_cmd *cmd)
{
	char	*ret;
	char	*line_read;

	ret = NULL;
	set_here_doc_signals();
	while (TRUE)
	{
		line_read = readline("> ");
		if (!line_read || ft_str_cmp(line_read, cmd->input->limiter) == 0
			|| get_exit_code() == 130)
		{
			if (!ret)
				write(cmd->input->here_doc_pipe[1], "", 1);
			else
				write(cmd->input->here_doc_pipe[1], ret, ft_strlen(ret));
			ret = ft_free(ret);
			set_interactiv_signals();
			return (SUCCESS);
		}
		ret = join_lines(&line_read, &ret);
		if (!ret)
			return (free(ret), free(line_read), MALLOC_ERROR);
	}
}

t_error	here_docs(t_lstd *current)
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
