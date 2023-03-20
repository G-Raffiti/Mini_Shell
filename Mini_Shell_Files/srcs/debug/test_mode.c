#include "../../../Lib_FT/incs/libft.h"
#include "mini_shell.h"
/*
//
// Created by rbonneva on 17/02/23.
//
t_bool test = FALSE;
t_bool test_mode()
{
	return (test);
}
void	set_test_mode()
{
	test = TRUE;
}

int test_minishell(char *line, t_mini_shell *ms)
{
	clear_cmds(&(ms->cmds), free_cmd);
	if (is_empty_line(line))
		return get_exit_code();
	if (parse_line(ms, line) == ERROR)
		return get_exit_code();
	set_exit_code(0);
	exec_cmds(ms);
	return get_exit_code();
}
 */