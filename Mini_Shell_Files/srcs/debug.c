//
// Created by rbonneva on 30/01/23.
//

#include "../incs/mini_shell.h"

void	print_debug_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_cmd	*cmd;
	char	*is_valid;
	int		i;

	current = ft_lstd_first(ms->cmds);
	while (current)
	{
		cmd = get(current);
		if (cmd->cmd)
			printf("CMD: %s | ", cmd->cmd[0]);
		else
			printf("NO_COMMAND | ");
		printf("PATH: %s | FDS: in(%d) out(%d) | ",
			cmd->path, cmd->input->fd, cmd->output->fd);
		is_valid = cmd->is_valid ? "Yes" : "No";
		printf("IS_VALID? %s\n", is_valid);
		printf("RAW_CMD: %s | ", cmd->raw_cmd);
		printf("PARSED_CMD: ");
		i = 0;
		while (cmd->cmd[i])
		{
			printf("%s / ", cmd->cmd[i]);
			i++;
		}
		current = current->next;
	}
}