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

static t_error	exec_here_doc(t_mini_shell *ms, t_here_docs *here)
{
	char	*ret;
	char	*line_read;

	ret = NULL;
	set_here_doc_signals();
	while (TRUE)
	{
		line_read = readline("> ");
		if (!line_read || ft_str_cmp(line_read, here->limiter) == 0
			|| get_exit_code() == 130)
		{
			expand_here_doc(ms, &ret, here);
			if (!ret)
				write(here->pipe_h[1], "", 1);
			else
				write(here->pipe_h[1], ret, ft_strlen(ret));
			ret = ft_free(ret);
			here->limiter = ft_free(here->limiter);
			return (SUCCESS);
		}
		ret = join_lines(&line_read, &ret);
		if (!ret)
			return (free(ret), free(line_read), MALLOC_ERROR);
	}
}

t_error	here_docs(t_mini_shell *ms, t_lstd *current)
{
	t_cmd	*cmd;
	t_lstd 	*cur_h;

	while (current)
	{
		cmd = get(current);
		cur_h = cmd->input->here_docs;
		while (cur_h)
		{
			if (exec_here_doc(ms, (t_here_docs *)cur_h->content) ==
			MALLOC_ERROR)
				return (MALLOC_ERROR);
			if (cur_h->next || cmd->input->type == IN_REDIR)
			{
				close(((t_here_docs *)cur_h->content)->pipe_h[0]);
				close(((t_here_docs *)cur_h->content)->pipe_h[1]);
			}
			cur_h = cur_h->next;
		}
		current = current->next;
	}
	return (SUCCESS);
}
