//
// Created by Raphael Bonneval on 1/24/23.
//

// TODO [Raphael] : install brew & Readline
// TODO [Raphael] : ingnore leaks

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../Lib_FT/incs/libft.h"

char	*read_line(void)
{
	char	*line;
	line = readline("ms_> ");
	if (line && ft_strlen(line) > 0)
		add_history(line);
	return (line);
}