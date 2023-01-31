//
// Created by Raphael Bonneval on 1/24/23.
//

// TODO [Raphael] : install brew & Readline
// TODO [Raphael] : ingnore leaks

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../Lib_FT/incs/libft.h"
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

char	*read_line(void)
{
	char	*line;
	printf(COLOR_BOLD "ms > " COLOR_OFF);
	line = readline("");
	if (line && ft_strlen(line) > 0)
		add_history(line);
	return (line);
}