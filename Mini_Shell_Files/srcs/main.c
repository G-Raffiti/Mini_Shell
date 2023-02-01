
#include <stdio.h>
#include "../incs/mini_shell.h"

static void	loop(t_mini_shell *ms)
{
	char	*line;

	while (TRUE)
	{
		line = read_line();
		if (!line)
			return ;
		dprintf(1, "line = [%s] | ", line);
		if (parse_line(ms, line) == ERROR)
		{
			clear_cmds(&(ms->cmds), free_cmd);
			line = ft_free(line);
			continue;
		}
		print_debug_cmds(ms);
		if (ft_str_cmp("exit", get(ms->cmds)->cmd[0]) == 0)
		{
			line = ft_free(line);
			clear_cmds(&(ms->cmds), free_cmd);
			exit_end_program(ms);
		}
		exec_cmds(ms);
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
		exit_malloc(ms);
	get_env(ms, env);
	get_all_paths(ms, ms->env_dict);
	//debug_mini_shell(ms);
	loop(ms);
	exit_end_program(ms);
}
