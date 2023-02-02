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
		printf("PATH: %s | FDS: <%s (%d) >%s (%d) | ",
			cmd->path, cmd->input->name, cmd->input->fd,cmd->output->name,
			cmd->output->fd);
		is_valid = cmd->is_valid ? "Yes" : "No";
		printf("IS_VALID? %s | ", is_valid);
		printf("RAW_CMD: [%s] | ", cmd->raw_cmd);
		printf("PARSED_CMD: ");
		i = 0;
		while (cmd->cmd[i])
		{
			printf("[%s] ", cmd->cmd[i]);
			i++;
		}
		current = current->next;
		printf("\n");
	}
	printf("\n");
}


void	debug_mini_shell(t_mini_shell *ms)
{
	printf("env %p\n", ms->env);
	if (ms->env)
	{
		int i = -1;
		while (ms->env[++i])
			printf("ms->env line %d: - %s\n", i, ms->env[i]);
	}
	printf("\nenv_dict %p\n", ms->env_dict);
	if (ms->env_dict)
	{
		t_lstd *current = ms->env_dict;
		while (current)
		{
			printf("env_dict: key: {%s} value: {%s}\n", get_env_dict(current)
			->key,
				get_env_dict(current)->value);
			current = current->next;
		}
	}
	printf("\npaths %p\n", ms->paths);
	if (ms->paths)
	{
		int i = -1;
		while (ms->paths[++i])
			printf("PATH[%d]: %s\n", i, ms->paths[i]);
	}
	printf("cmds %p\n\n", ms->cmds);
}

void debug_fd(t_mini_shell *ms, t_cmd *cmd)
{
	dprintf(2, "{cmd: %s | files: pipe=(%d-%d) ret=(%d-%d) | fds=(%d-%d)}\n",
			cmd->cmd[0],
	ms->pipe[0],
			ms->pipe[1], ms->pipe_retour[0], ms->pipe_retour[1],
			cmd->input->fd, cmd->output->fd);
}