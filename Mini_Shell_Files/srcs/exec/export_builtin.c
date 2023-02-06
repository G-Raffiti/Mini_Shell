// created by aurel

#include "../../incs/mini_shell.h"

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
			write(STDOUT_FILENO, &(ms->env_sort)[i][j], 1);
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

t_error	replace_in_envs(t_mini_shell *ms, t_lstd *current, char *arg, int pos)
{
	if (pos == 0)
	{
		dprintf(2, "no_arg/no_equal");
		return(SUCCESS);
	}
	else if (!*arg)
	{
		//TODO : Modify in envs
		replace_in_chosen_env(ms, get_env_dict(current->content), "\"\"", 1);
		fill_export_env(ms);
	}
	return (SUCCESS);
}

t_error	export_arg(t_mini_shell *ms, char *arg, int pos)
{
	t_lstd	*current_sorted;

	if (pos != 0)
		arg[pos] = '\0';
	current_sorted = ft_lstd_find(ms->env_sort_dict, arg, find_in_dict_sorted);
	if (current_sorted)
	{
		if (pos != 0)
			arg = (arg + pos + 1);
		//dprintf(2, "ARG='%s'", arg);
		replace_in_envs(ms, current_sorted, arg, pos);
	}
//	else
//		add_in_envs(ms, arg);
	return (SUCCESS);
}

void	get_equal_char_pos(char *arg, int *pos)
{
	*pos = 0;
	while (arg[*pos] && arg[*pos] != '=')
		(*pos)++;
	if (*pos == (int)ft_strlen(arg))
		*pos = 0;
}

t_error	ft_export(t_mini_shell *ms, t_cmd *cmd)
{
	int		i;
	int 	pos;

	i = 0;
	ms->exported = TRUE;
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
			{
				get_equal_char_pos(cmd->cmd[i], &pos);
				if (export_arg(ms, cmd->cmd[i], pos) == MALLOC_ERROR)
					return (MALLOC_ERROR);
			}
		}
	}
	return (SUCCESS);
}

