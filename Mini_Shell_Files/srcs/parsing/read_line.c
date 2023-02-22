#include <stdio.h>//TODO : delete at school
#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"
#include <termios.h>

void	handle_readline_conflict_keybinding()
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VLNEXT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*read_line(void)
{
	char	*line;

	//handle_readline_conflict_keybinding();
	set_interactiv_signals();
	if (get_exit_code() == 0)
		line = readline(PROMPT""GREEN"-▶ "WHITE);
	else
		line = readline(PROMPT""RED"-▶ "WHITE);
	if (line && ft_strlen(line) > 0 && !is_empty_line(line))
		add_history(line);
	return (line);
}
