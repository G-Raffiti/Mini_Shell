//
// Created by Raphael Bonneval on 1/24/23.
//

#include <sys/fcntl.h>
#include "../../incs/mini_shell.h"

/// TO use every where
int	set_quote_state(char c, char *quote)
{
	if (c == *quote && *quote != 0)
		*quote = 0;
	else if (*quote == 0 && c == '\'')
		*quote = '\'';
	else if (*quote == 0 && c == '\"')
		*quote = '\"';
	return (*quote);
}

t_error	create_cmds(t_mini_shell *mini_shell, char *line)
{
	int		i;
	char **raw_cmds;
	t_lstd *current;
	t_cmd *cmd;

	raw_cmds = split_pipe(line);
	if (!raw_cmds)
		return (MALLOC_ERROR);
	i = 0;
	while(raw_cmds[i])
	{
		if(new_cmd(&cmd) == MALLOC_ERROR)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds, free_cmd),
					MALLOC_ERROR);
		cmd->raw_cmd = ft_strdup(raw_cmds[i]);
		if (!cmd->raw_cmd)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds, free_cmd),
					MALLOC_ERROR);
		current = ft_lstd_new(cmd);
		if (!current)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds, free_cmd),
					MALLOC_ERROR);
		ft_lstd_push_back_elem(&mini_shell->cmds, current);
		i++;
	}
	raw_cmds = free_split(raw_cmds);
	return (SUCCESS);
}

t_error	fill_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_error	status;

	current = ft_lstd_first(ms->cmds);
	while (current)
	{
		status = open_files(ms, get(current));
		debug(1, "open_Files"GREEN" DONE "GREY"| "WHITE);
		if (status == MALLOC_ERROR)
			return (MALLOC_ERROR);
		else if (status == ERROR)
			return (ERROR);
		replace_dollar_before_quotes(get(current));
		if (replace_dollars(ms, get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		// TODO [Aurel]: find_in_dict and replace $ARG with env_lst key/value
		if (is_empty_line(get(current)->raw_cmd))
			return (ERROR);
		if (get_cmd(get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		debug(1, "get_cmd"GREEN" DONE "GREY"| "WHITE);
		if (get_path(ms, get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		debug(1, "get_path"GREEN" DONE "GREY"| "WHITE);
		set_builtin(current);
		current = current->next;
	}
	return (SUCCESS);
}

t_error	parse_line(t_mini_shell *ms, char *line)
{
	t_error status;
	if (check_line(line) == ERROR)
		return (ERROR);
	debug(1, "check"GREEN" DONE "GREY"| "WHITE);
	if (create_cmds(ms, line) == MALLOC_ERROR)
		return (free(line), exit_malloc(ms, "parsing: crete_cmds"));
	debug(1, "crete cmds"GREEN" DONE "GREY"| "WHITE);
	status = fill_cmds(ms);
	if (status == MALLOC_ERROR)
		return (free(line), exit_malloc(ms, "parsing: fill_cmds"));
	else if (status == ERROR)
		return (parse_error("syntax error near unexpected token `<'", 2));
	debug(1, "fill cmds"GREEN" DONE "GREY"\n"WHITE);
	return (SUCCESS);
}
