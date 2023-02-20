//
// Created by rbonneva on 2/20/23.
//

#include <signal.h>
#include <readline/readline.h>
#include "../../incs/mini_shell.h"

void	here_doc_handler(int signum)
{
	if (signum == SIGINT)
	{
		set_exit_code(130);
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	else if (signum == SIGQUIT)
	{
		printf("\b \b \b\b \b");
		rl_redisplay();
		set_exit_code(0);
	}
}

void	interactiv_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		set_exit_code(130);
	}
	else if (signum == SIGQUIT)
	{
		printf("\b \b \b\b \b");
		rl_redisplay();
		set_exit_code(0);
	}
}

void	exec_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		set_exit_code(130);
	}
	if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		set_exit_code(131);
	}
}
