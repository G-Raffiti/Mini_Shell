//
// Created by aurel on 2/4/23.
//

#include "../incs/mini_shell.h"

void	display_export(t_mini_shell *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->env_sort[i])
	{
		j = 0;
		while (ms->env_sort[i][j])
		{
			write(STDOUT_FILENO, &(ms->env_sort)[i], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

int export_name_valid(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (valid_id_export(arg[i]) == 0)
			return (0);
		i++;
	}
	return (i);
}

t_error	export_arg(t_mini_shell *ms, char *arg)
{
	(void)arg;
	(void)ms;

	return (SUCCESS);
}

t_error	ft_export(t_mini_shell *ms, t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd->cmd[1])
	{
		display_export(ms);
		return(SUCCESS);//TODO : afficher env_export
	}
	else
	{
		while (cmd->cmd[++i])
		{
			if (!export_name_valid(cmd->cmd[i]))
				dprintf(2, "(%d)[%s] :not a valid arg export\n", i, cmd->cmd[i]);//TODO : return msg_error
			else
				if (export_arg(ms ,cmd->cmd[i]) == MALLOC_ERROR)
					return (MALLOC_ERROR);
		}
	}
	return (SUCCESS);
}

