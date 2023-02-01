//
// Created by Raphael Bonneval on 1/24/23.
//

#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"

char	*read_line(void)
{
	char	*line;
	line = readline(PROMPT);
	if (line && ft_strlen(line) > 0)
		add_history(line);
	return (line);
}