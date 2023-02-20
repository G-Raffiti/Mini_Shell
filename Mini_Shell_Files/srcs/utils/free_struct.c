
#include "../../incs/mini_shell.h"
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
	fd->limiter = ft_free(fd->limiter);
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

void	*free_dict(void *pt)
{
	ft_free(get_env_dict((t_env_arg*)pt)->key);
	ft_free(get_env_dict((t_env_arg*)pt)->value);
	ft_free((t_env_arg*)pt);
	return (NULL);
}

void	*free_mini_shell(t_mini_shell *ms)
{
	if (!ms)
		return (NULL);
	if (ms->env)
		ms->env = free_split(ms->env);
	if (ms->env_sort)
		ms->env = free_split(ms->env_sort);
	ft_lstd_clear(&ms->env_dict, free_dict);
	ft_lstd_clear(&ms->env_sort_dict, free_dict);
	if (ms->paths)
		ms->paths = free_split(ms->paths);
	clear_cmds(&ms->cmds, free_cmd);
	close(ms->stds[0]);
	close(ms->stds[1]);
	ms = ft_free(ms);
	return (NULL);
}