
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../incs/mini_shell.h"

static void	loop(t_mini_shell *ms)
{
	char	*line;

	while (TRUE)
	{
		line = read_line();
		if (!line)
			return;
<<<<<<< HEAD
		if (is_empty_line(line))
		{
			line = ft_free(line);
			continue;
		}
		set_exit_code(0);
=======
>>>>>>> main
		debug(3, WHITE"line"GREY" = ["WHITE, line,GREY"] | "WHITE);
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
		set_exit_code(0);
		exec_cmds(ms);
		clear_cmds(&(ms->cmds), free_cmd);
		line = ft_free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*ms;

	if (argc == 2 && ft_str_cmp(argv[1], "debug") == 0)
		enable_debug();
	printf("☠  ---Welcome to mini Hell--- ☠ \n");
//	if (env == NULL)
//	{
//		if (generate_minimal_env(&env) == MALLOC_ERROR)
//			return (exit_malloc(NULL, "main: generate_minimal_env"));
//	}
	if (new_mini_shell(&ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: new_mini_shell");
	get_env(ms, env);
	get_all_paths(ms, ms->env_dict);
	loop(ms);
	exit_end_program(ms);
}
