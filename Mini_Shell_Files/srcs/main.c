
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../incs/mini_shell.h"
#include "debug.h"

static void	loop(t_mini_shell *ms)
{
	char	*line;

	while (TRUE)
	{
		line = read_line();
		if (!line)
			return;
		set_exit_code(0);
		dprintf(1, "line = [%s] | ", line);
		if (parse_line(ms, line) == ERROR)
		{
			clear_cmds(&(ms->cmds), free_cmd);
			line = ft_free(line);
			continue;
		}
		debug_all_cmds(ms);
		if (ft_str_cmp("exit", get(ms->cmds)->cmd[0]) == 0)
		{
			line = ft_free(line);
			clear_cmds(&(ms->cmds), free_cmd);
			exit_end_program(ms);
		}
		exec_cmds(ms);
		//if (errno != 10)
		//	set_exit_code(errno);
		//printf(RED"ERROR="WHITE" %d -> %s\n", get_exit_code(), strerror
		//(get_exit_code()));
		clear_cmds(&(ms->cmds), free_cmd);
		line = ft_free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*ms;

	(void) argc;
	(void) argv;
	printf("Hello Hell !\n");
	if (new_mini_shell(&ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: new_mini_shell");
	get_env(ms, env);
	get_all_paths(ms, ms->env_dict);
	loop(ms);
	exit_end_program(ms);
}
