
#include "mini_shell.h"

int print_error_env(t_mini_shell *ms, char *first_arg, int in_pipe)
{
	t_lstd	*path;
	char	*value;

	(void)first_arg;
	(void)in_pipe;
	path = ft_lstd_find(ms->env_sort_dict, "PATH", find_in_dict_sorted);
	if (path)
		value = get_env_dict(path->content)->value;
	if (ft_str_cmp(value, "=\"\"") == 0 \
				|| ft_str_cmp(value, "") == 0)
		dprintf(2, "no such file or directory -> to set\n");
	else
		return (2);
	return (1);
}

t_error	ft_env(t_mini_shell *ms, t_cmd *cmd, int in_pipe)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	error = print_error_env(ms, cmd->cmd[1], in_pipe);
	if (cmd->cmd[1] && error == 1)
		return (ERROR);
	else if (error == 2)
	{
		while (ms->env[++i])
		{
			j = 0;
			while (ms->env[i][j])
			{
				write(STDOUT_FILENO, &ms->env[i][j], 1);
				j++;
			}
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (SUCCESS);
}
