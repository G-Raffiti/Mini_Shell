
#include "../incs/mini_shell.h"
#include <stdlib.h>

void	*ft_free(void *pt)
{
	if (pt)
		free(pt);
	return (NULL);
}

void	*free_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
		split[i] = ft_free(split[i]);
	split = ft_free(split);
	return (NULL);
}

void	*free_fd(t_fd *fd)
{
	if (!fd)
		return (NULL);
	fd->name = ft_free(fd->name);
	free(fd);
	return (NULL);
}

void	*free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd->raw_cmd)
		cmd->raw_cmd = ft_free(cmd->raw_cmd);
	if (cmd->path)
		cmd->path = ft_free(cmd->path);
	if (cmd->cmd)
		cmd->cmd = free_split(cmd->cmd);
	if (cmd->input)
		cmd->input = free_fd(cmd->input);
	if (cmd->output)
		cmd->output = free_fd(cmd->output);
	cmd = ft_free(cmd);
	return (NULL);
}

void	*free_mini_shell(t_mini_shell *mini_shell)
{
	if (!mini_shell)
		return (NULL);
	if (mini_shell->env)
		mini_shell->env = free_split(mini_shell->env);
	ft_lstd_clear(&mini_shell->env_dict, ft_free);
	if (mini_shell->paths)
		mini_shell->paths = free_split(mini_shell->paths);
	clear_cmds(&mini_shell->cmds, free_cmd);
	mini_shell = ft_free(mini_shell);
	return (NULL);
}