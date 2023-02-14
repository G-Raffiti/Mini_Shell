//
// Created by aucaland on 2/10/23.
//

#include "../../incs/mini_shell.h"
# include <readline/readline.h>

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
		printf("\b \b \b\b \b");//attention peut etre de la merde,
		// utiliser tcgetattr si jamais.
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

void	set_interactiv_signals()
{
	struct sigaction action;

	action.sa_handler = interactiv_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	set_exec_signals()
{
	struct sigaction action;

	action.sa_handler = exec_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}