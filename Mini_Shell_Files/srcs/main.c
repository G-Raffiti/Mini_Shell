//TODO : RECAP ft_env : doc in file 'modif_env.c' so RTFM , kiss
//TODO : PS ===> Tu peux pas remove dans l'ft_env, seulement remplacer/add. (enfin sinon il suffit de faire un remove list)
//TODO : PS2 ===> si tu regenere l'ft_env en creant un char ** pour je ne sais quelle raison, il te suffit de le balance dans get_env au debut du main la suite se fait toute seule)
#include <stdio.h>
#include <errno.h>
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
		debug(3, WHITE"line"GREY" = ["WHITE, line,GREY"] | "WHITE);
		if (parse_line(ms, line) == ERROR)
			continue;
		debug_all_cmds(ms);
		set_exit_code(0);
		exec_cmds(ms);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*ms;

	if (argc == 2 && ft_str_cmp(argv[1], "debug") == 0)
		enable_debug();
	printf("☠  ---Welcome to mini Hell--- ☠ \n");
	if (new_mini_shell(&ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: new_mini_shell");
	if (get_env(ms, env) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_env");
	if (get_export_env(ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_export_env");
	get_all_paths(ms, ms->env_dict);
	//debug_mini_shell(ms);
	loop(ms);
	exit_end_program(ms);
}
