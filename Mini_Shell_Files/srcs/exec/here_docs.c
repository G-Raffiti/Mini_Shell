/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:20 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 17:46:39 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	write_in_pipe(const t_here_docs *here, const char *ret)
{
	if (!ret)
		write(here->pipe_h[1], "", 1);
	else
		write(here->pipe_h[1], ret, ft_strlen(ret));
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
			if (!line_read && get_exit_code() != 130)
				write(1, "\n", 1);
			expand_here_doc(ms, &ret, here);
			write_in_pipe(here, ret);
			ret = ft_free(ret);
			here->limiter = ft_free(here->limiter);
			if (get_exit_code() == 130)
				return (ERROR);
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
	t_lstd	*cur_h;

	while (current)
	{
		cmd = get(current);
		cur_h = cmd->input->here_docs;
		while (cur_h)
		{
			if (exec_here_doc(ms, (t_here_docs *)cur_h->content) == \
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
