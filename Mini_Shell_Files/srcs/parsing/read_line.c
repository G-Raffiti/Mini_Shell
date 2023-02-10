//
// Created by Raphael Bonneval on 1/24/23.
//
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"
#include "../../incs/debug.h"

char	*read_line(void)
{
	char	*line;

	set_interactiv_signals();
	if (get_exit_code() == 0 && (get_exit_code() != 131))
		line = readline(PROMPT""GREEN"-▶ "WHITE);
	else if (get_exit_code() != 131)
		line = readline(PROMPT""RED"-▶ "WHITE);
	if (line && ft_strlen(line) > 0 && !is_empty_line(line))
		add_history(line);
	return (line);
}