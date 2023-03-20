#include <stdio.h>//TODO : delete at school
#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"
# include <signal.h>

char	*read_line(void)
{
	char	*line;


	set_interactiv_signals();
	line = readline(PROMPT"-▶ "WHITE);
	if (line && ft_strlen(line) > 0 && !is_empty_line(line))
		add_history(line);
	return (line);
}
