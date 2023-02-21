#include "../../incs/mini_shell.h"

void	initialize_struct_dollar(t_dollar *dlr, t_cmd *cmds)
{
	dlr->nbr = 0;
	dlr->start_dol = 0;
	dlr->len_prev = 0;
	dlr->quote = 0;
	dlr->prev_is_arg = 0;
	dlr->raw_cmd = cmds->raw_cmd;
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
