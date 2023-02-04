//
// Created by aurel on 2/4/23.
//

#include "../incs/mini_shell.h"

int export_name_valid(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (valid_id_export(arg[i]) == 0)
			return (0);
		i++;
	}
	return (i);
}

t_error	export_cmd(t_mini_shell *ms, char *arg)
{

}

t_error	export(t_mini_shell *ms, t_cmd *cmd)
{
	(void)ms;
	int i = 0;

	if (!cmd->cmd[1])
	{
		dprintf(2, "display env_export\n");
		return(SUCCESS);//TODO : afficher env_export
	}
	else
	{
		while (cmd->cmd[i])
		{
			if (!export_name_valid(cmd->cmd[i]))
			{
				dprintf(2, "not a valid arg export\n");
				return ((SUCCESS));//TODO : return msg_error
			}
			else
				if (export_cmd(ms ,cmd->cmd[i]) == MALLOC_ERROR)
					return (MALLOC_ERROR);
		}
	}

	return (SUCCESS);
}

