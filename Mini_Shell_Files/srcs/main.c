
#include <stdio.h>
#include "../incs/mini_shell.h"

static void	loop(t_mini_shell *mini_shell)
{
	char	*line;

	while (TRUE)
	{
		line = read_line();
		if (!line)
			return ;
		dprintf(1, "line = \"%s\" | ", line);
		if (parse_line(mini_shell, line) == ERROR)
		{
			clear_cmds(&(mini_shell->cmds), free_cmd);
			line = ft_free(line);
			continue;
		}
		print_debug_cmds(mini_shell);
		//exec_cmds(mini_shell);
		clear_cmds(&(mini_shell->cmds), free_cmd);
		line = ft_free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	*mini_shell;

	(void) argc;
	(void) argv;
	printf("Hello Hell !\n");
	if (new_mini_shell(&mini_shell) == MALLOC_ERROR)
		exit_malloc(mini_shell);
	get_env(mini_shell, env);
	get_all_paths(mini_shell, mini_shell->env_dict);
	set_env(mini_shell, env);
	//debug_mini_shell(mini_shell);
	loop(mini_shell);
	exit_end_program(mini_shell);
}
