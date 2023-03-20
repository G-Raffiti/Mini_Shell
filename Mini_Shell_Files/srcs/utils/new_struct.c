/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:32 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:32 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

void	initialize_struct_dollar(t_dollar *dlr, t_cmd *cmds, char **here_doc)
{
	dlr->nbr = 0;
	dlr->start_dol = 0;
	dlr->len_prev = 0;
	dlr->quote = 0;
	dlr->prev_is_arg = 0;
	if (cmds)
	{
		dlr->raw_cmd = cmds->raw_cmd;
		dlr->here_doc = NULL;
	}
	else if (*here_doc)
	{
		dlr->here_doc = *here_doc;
		dlr->raw_cmd = NULL;
	}
}

t_error	new_env_arg(t_env_arg **env_dict)
{
	*env_dict = ft_calloc(1, sizeof(t_env_arg));
	if (!*env_dict)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	new_fd(t_fd **fd)
{
	*fd = ft_calloc(1, sizeof(t_fd));
	if (!*fd)
		return (MALLOC_ERROR);
	(*fd)->type = PIPE_REDIR;
	(*fd)->fd = -2;
	return (SUCCESS);
}

t_error	new_cmd(t_cmd **cmd)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		return (MALLOC_ERROR);
	if (new_fd(&((*cmd)->input)) == MALLOC_ERROR
		|| new_fd(&((*cmd)->output)) == MALLOC_ERROR)
	{
		*cmd = free_cmd(*cmd);
		return (MALLOC_ERROR);
	}
	(*cmd)->is_builtin = FALSE;
	return (SUCCESS);
}

t_error	new_mini_shell(t_mini_shell **mini_shell)
{
	*mini_shell = ft_calloc(1, sizeof(t_mini_shell));
	if (!*mini_shell)
		return (MALLOC_ERROR);
	(*mini_shell)->pipe[0] = 0;
	(*mini_shell)->pipe[1] = 1;
	return (SUCCESS);
}
