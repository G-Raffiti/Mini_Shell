//
// Created by aucaland on 2/10/23.
//

#include "../../incs/mini_shell.h"
#include <signal.h>

void	set_interactiv_signals(void)
{
	struct sigaction	action;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	action.sa_handler = interactiv_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	set_exec_signals(void)
{
	struct sigaction	action;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	action.sa_handler = exec_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}

void	set_here_doc_signals(void)
{
	struct sigaction	action;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	action.sa_handler = here_doc_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}
