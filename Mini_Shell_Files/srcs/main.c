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
			return;
		if (is_empty_line(line))
			continue;
		debug(3, WHITE"line"GREY" = ["WHITE, line,GREY"] | "WHITE);//delete
		if (parse_line(ms, line) == ERROR)
			continue;
		debug_all_cmds(ms);//delete
		set_exit_code(0);
		exec_cmds(ms);
		if (test_mode())//delete
		{//delete
			clear_cmds(&(ms->cmds), free_cmd);//delete
			line = ft_free(line);//delete
			exit(get_exit_code());//delete
		}//delete
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*ms;
	t_bool			env_malloced;

	env_malloced = FALSE;
	if (argc == 2 && ft_str_cmp(argv[1], "debug") == 0)//delete
		enable_debug();//delete
	if (argc == 2 && ft_str_cmp(argv[1], "test") == 0)//delete
		set_test_mode();//delete
	if (!test_mode() && (!argv[1] || (argv[1] && ft_strncmp(argv[1],"-c",3))))//delete
		printf("☠  ---Welcome to mini Hell--- ☠ \n");//delete
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
		free_split(env);
	if (get_export_env(ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_export_env");
	get_all_paths(ms, ms->env_dict);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))//delete
	{//delete
		int exit_status = test_minishell(argv[2], ms);//delete
		exit(exit_status);//delete
	}//delete
	loop(ms);
	exit_end_program(ms, EXIT_SUCCESS);
}
