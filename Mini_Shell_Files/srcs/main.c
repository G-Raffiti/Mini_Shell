
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

void	debug_mini_shell(t_mini_shell *ms)
{
	printf("------KEYS------\n\n env %p\n", ms->env);
	if (ms->env)
	{
		int i = -1;
		while (ms->env[++i])
			printf("env line %d: %s\n", i, ms->env[i]);
	}
	printf("env_dict %p\n\n\n ------KEYS------\n\n\n", ms->env_dict);
	if (ms->env_dict)
	{
		t_lstd *current = ms->env_dict;
		while (current)
		{
			printf("env_dict: key: %s = %s", get_env_dict(current)->key,
				get_env_dict(current)->value);
			printf("\n");
			current = current->next;
		}
	}
	printf("paths %p\n", ms->paths);
	if (ms->paths)
	{
		int i = -1;
		while (ms->paths[++i])
			printf("env line %d: %s\n", i, ms->paths[i]);
	}
	printf("cmds %p\n\n", ms->cmds);
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
	set_env(mini_shell, env);
	debug_mini_shell(mini_shell);
	loop(mini_shell);
	exit_end_program(mini_shell);
}
