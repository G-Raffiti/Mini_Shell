#include <stdio.h>
#include <string.h>
#include "../incs/mini_shell.h"

static void	loop(t_mini_shell *ms)
{
	char	*line;

	line = NULL;
	while (TRUE)
	{
		clear_cmds(&(ms->cmds), free_cmd);
		line = ft_free(line);
		line = read_line();
		if (!line)
			return ;
		if (is_empty_line(line))
			continue ;
		if (parse_line(ms, line) == ERROR)
			continue;
		exec_cmds(ms);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*ms;
	t_bool			env_malloced;

	(void) argc;
	(void) argv;
	env_malloced = FALSE;
	if (new_mini_shell(&ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: new_mini_shell");
	if (!env[0])
	{
		env = regen_env();
		env_malloced = TRUE;
	}
	if (!env)
		exit_malloc(ms, "env: dup_env");
	if (get_env(ms, env) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_env");
	if (env_malloced)
		env = free_split(env);
	if (get_export_env(ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_export_env");
	get_all_paths(ms, ms->env_dict);
	loop(ms);
	exit_end_program(ms, EXIT_SUCCESS);
}
