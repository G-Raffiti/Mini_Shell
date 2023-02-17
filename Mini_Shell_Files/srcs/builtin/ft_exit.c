//
// Created by rbonneva on 16/02/23.
//

#include "../../incs/mini_shell.h"

// TODO exit arguments atoi etc ...
t_error	ft_exit(t_mini_shell *ms)
{
	close(ms->stds[0]);
	close(ms->stds[1]);
	return (exit_end_program(ms));
}