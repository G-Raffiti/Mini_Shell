/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:51:40 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 20:17:26 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(fd);
	return (NULL);
}

void	*free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd->input)
		cmd->input = free_fd(cmd->input);
	if (cmd->output)
		cmd->output = free_fd(cmd->output);
	if (cmd->path)
		cmd->path = ft_free(cmd->path);
	if (cmd->cmd)
		cmd->cmd = free_split(cmd->cmd);
	if (cmd->args)
		cmd->args = free_split(cmd->args);
	cmd = ft_free(cmd);
	return (NULL);
}

void	*free_mini_shell(t_mini_shell *mini_shell)
{
	if (!mini_shell)
		return (NULL);
	if (mini_shell->env)
		mini_shell->env = free_split(mini_shell->env);
	if (mini_shell->paths)
		mini_shell->paths = free_split(mini_shell->paths);
	if (mini_shell->cmds)
		ft_lstd_clear(&mini_shell->cmds, (void (*)(void *))free_cmd);
	mini_shell = ft_free(mini_shell);
	return (NULL);
}