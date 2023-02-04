
#include "../incs/mini_shell.h"

int print_error_env(char *first_arg)
{
	if (first_arg && first_arg[0] && ft_str_cmp(first_arg, "test") == 0)
		return (2);
	else if (first_arg && first_arg[0] != '-')
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(first_arg, 2);
		ft_putstr_fd("‘", 2);
		ft_putendl_fd(": No such file or directory\n", 2);
		return (1);
	}
	else if (first_arg && first_arg[0] == '-')
	{
		ft_putendl_fd("We do not handle this bro", 2);//TODO : talk about what to do : return nothing or return the messgae with option not handled, or return to execve
		return (2);
	}
	return (0);
}

void	env(t_mini_shell *ms, t_cmd *cmd)
{
	int	i;
	int	j;
	int	error;

	i = -1;

	error = print_error_env(cmd->cmd[1]);
	if (cmd->cmd[1] && error == 1)
		return ;
	else if (error == 2)
		return ;
	else
	{
		while (ms->env[++i])
		{

			j = 0;
			while (ms->env[i][j])
			{
				if (write(STDOUT_FILENO, &ms->env[i][j], 1) != 1)
					dprintf(2, "pb ecriture");
				j++;
			}
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
