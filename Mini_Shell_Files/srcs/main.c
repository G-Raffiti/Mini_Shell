
#include <stdio.h>
#include "../incs/mini_shell.h"

static void	loop(t_mini_shell *mini_shell)
{
	char	*line;
	int		is_parent;

	while (TRUE)
	{
		printf("mini_shell$ ");
		line = read_line();
		if (!line)
			return ;
		if (parse_line(mini_shell, line) == ERROR)
			return ;
		is_parent = fork();
		if (!is_parent)
			exec_cmds(mini_shell);
		clear_cmds(&mini_shell->cmds);
		line = ft_free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	mini_shell;

	(void) argc;
	(void) argv;
	printf("Hello Hell !\n");
	if (new_mini_shell(&mini_shell) == MALLOC_ERROR)
		exit_malloc(&mini_shell);
	set_env(&mini_shell, env);
	loop(&mini_shell);
	exit_end_program(&mini_shell);
}
