
#include "../incs/mini_shell.h"
#include <stdlib.h>

t_error	new_fd(t_fd *fd)
{
	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (MALLOC_ERROR);
	fd->fd = 0;
	fd->open_mode = -1;
	return (SUCCESS);
}

t_error	new_cmd(t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (MALLOC_ERROR);
	cmd->raw_cmd = NULL;
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->args_cmd = NULL;
	if (new_fd(cmd->input) == MALLOC_ERROR
		|| new_fd(cmd->output) == MALLOC_ERROR)
	{
		cmd = free_cmd(cmd);
		return (MALLOC_ERROR);
	}
	cmd->is_builtin = FALSE;
	return (SUCCESS);
}

t_error	new_mini_shell(t_mini_shell *mini_shell)
{
	mini_shell = malloc(sizeof(t_mini_shell));
	if (!mini_shell)
		return (MALLOC_ERROR);
	mini_shell->env = NULL;
	mini_shell->env_lst = NULL;
	mini_shell->paths = NULL;
	mini_shell->cmds = NULL;
	mini_shell->pipe[0] = 0;
	mini_shell->pipe[1] = 1;
	return (SUCCESS);
}