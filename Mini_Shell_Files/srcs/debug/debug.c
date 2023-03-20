//
// Created by rbonneva on 30/01/23.
//

/*
#include <stdarg.h>
#include "../../incs/mini_shell.h"
#include "../../incs/debug.h"

int g_debug = 0;

t_bool	debug_mod(void)
{
	if (g_debug)
		return (TRUE);
	return (FALSE);
}

void	enable_debug(void)
{
	g_debug = 1;
}

void	debug(int ac, ...)
{
	if (!g_debug)
		return ;
	va_list ap;
	va_start(ap, ac);
	while (ac > 0)
	{
		dprintf(2, "%s", va_arg(ap, char *));
		ac--;
	}
	va_end(ap);


}

void	debug_cmd(t_cmd *cmd)
{
	if (!g_debug)
		return ;
	char	*is_valid;
	int		i;
	if (cmd->cmd)
		printf(WHITE"CMD: "YELLOW"%s "GREY"| ", cmd->cmd[0]);
	else
		printf("NO_COMMAND | ");
	printf("%sPATH: %s%s%s | ", WHITE, YELLOW, cmd->path, GREY);
	printf(WHITE"FD: input"GREY"["YELLOW"%s"GREY"="YELLOW"%d"GREY"] "
		WHITE"output"GREY"["YELLOW"%s"GREY"="YELLOW"%d"GREY"] | ",
		cmd->input->name == NULL ? "Pipe" : cmd->input->name, cmd->input->fd,
		cmd->output->name == NULL ? "Pipe" : cmd->output->name,
		cmd->output->fd);
	is_valid = cmd->is_builtin ? GREEN"Yes"GREY : RED"No"GREY;
	printf(WHITE"IS_BUILTIN? %s | ", is_valid);
	printf(WHITE"RAW_CMD: "GREY"["YELLOW"%s"GREY"] | ", cmd->raw_cmd);
	printf(WHITE"PARSED_CMD: "GREY);
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		printf("["YELLOW"%s"GREY"] ", cmd->cmd[i]);
		i++;
	}
	printf("%s\n", WHITE);
}

void	debug_all_cmds(t_mini_shell *ms)
{
	if (!g_debug)
		return ;
	t_lstd	*current;
	t_cmd	*cmd;

	current = ft_lstd_first(ms->cmds);
	while (current)
	{
		cmd = get(current);
		debug_cmd(cmd);
		current = current->next;
	}
	printf("\n");
}


void	debug_mini_shell(t_mini_shell *ms)
{
	if (!g_debug)
		return ;
	printf("ft_env %p\n", ms->env);
	if (ms->env)
	{
		int i = -1;
		while (ms->env[++i])
			printf("ms->ft_env line %d: - %s\n", i, ms->env[i]);
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
	if (!g_debug)
		return ;
	printf(WHITE"CMD: "YELLOW"%s"WHITE" FD: input"GREY"["YELLOW"%s"GREY"="YELLOW"%d"GREY"] "
			WHITE"output"GREY"["YELLOW"%s"GREY"="YELLOW"%d"GREY"] | "
			WHITE"PATH"GREY"["YELLOW"0"GREY"]="YELLOW"%d "
			WHITE"PATH"GREY"["YELLOW"1"GREY"]="YELLOW"%d"WHITE"\n",
			cmd->cmd[0],
			cmd->input->name == NULL ? "Pipe" : cmd->input->name, cmd->input->fd,
			cmd->output->name == NULL ? "Pipe" : cmd->output->name,
			cmd->output->fd, ms->pipe[0], ms->pipe[1]);
}
 */