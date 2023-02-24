#include <stdio.h>//TODO : delete at school
#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"

char	*read_line(void)
{
	char	*line;

	set_interactiv_signals();
	if (get_exit_code() == 0)
		line = readline(PROMPT""GREEN"-▶ "WHITE);
	else
		line = readline(PROMPT""RED"-▶ " WHITE);
	if (line && ft_strlen(line) > 0 && !is_empty_line(line))
		add_history(line);
	return (line);
}
