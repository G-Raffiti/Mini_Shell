/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:41 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/21 17:52:49 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>
#include "../../incs/mini_shell.h"

static t_error	chevron_out(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	cmd->output->type = type;
	if (cmd->output->fd > 0)
	{
		safe_close(ms, cmd->output->fd, "chevron_out");
		cmd->output->name = ft_free(cmd->output->name);
	}
	if (type == OUT_REDIR)
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	cmd->output->name = file_name;
	if (cmd->output->fd == -1)
		cmd->output->error = errno;
	return (SUCCESS);
}

static t_error	create_here_docs(t_mini_shell *ms, t_cmd *cmd, char *limiter,
			t_chevron *type)
{
	t_here_docs	*here_doc;
	t_lstd		*elem;

	here_doc = ft_calloc(1, sizeof(t_here_docs));
	if (!here_doc)
		return (MALLOC_ERROR);
	if (*type == HERE_DOC_QUOTE_REDIR)
	{
		here_doc->have_to_expand = FALSE;
		*type = HERE_DOC_REDIR;
	}
	else
		here_doc->have_to_expand = TRUE;
	here_doc->limiter = limiter;
	safe_pipe(ms, here_doc->pipe_h, "create_here_docs");
	elem = ft_lstd_new(here_doc);
	if (!elem)
		return (free(here_doc), MALLOC_ERROR);
	ft_lstd_push_back_elem(&cmd->input->here_docs, elem);
	return (SUCCESS);
}

t_error	chevron_in(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	if (cmd->input->fd == -1)
		return (ERROR);
	if (type == OUT_REDIR || type == APPEND_REDIR)
		return (chevron_out(ms, cmd, type, file_name));
	if (cmd->input->fd > 0)
	{
		safe_close(ms, cmd->input->fd, "chevron_in");
		cmd->input->name = ft_free(cmd->input->name);
	}
	if (type == IN_REDIR)
	{
		cmd->input->name = file_name;
		cmd->input->fd = open(file_name, O_RDONLY);
	}
	else if ((type == HERE_DOC_REDIR || type == HERE_DOC_QUOTE_REDIR)
		&& create_here_docs(ms, cmd, file_name, &type) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (cmd->input->fd == -1)
		cmd->input->error = errno;
	cmd->input->type = type;
	return (SUCCESS);
}

t_chevron	get_chevron_type(char *str)
{
	t_chevron	type;

	type = -1;
	if (*str == '<' && *(str + 1) != '<')
		type = IN_REDIR;
	else if (*str == '>' && *(str + 1) != '>')
		type = OUT_REDIR;
	else if (*str == '<' && *(str + 1) == '<')
	{
		type = HERE_DOC_REDIR;
		*str = ' ';
		str++;
	}
	else if (*str == '>' && *(str + 1) == '>')
	{
		type = APPEND_REDIR;
		*str = ' ';
		str++;
	}
	*str = ' ';
	return (type);
}
