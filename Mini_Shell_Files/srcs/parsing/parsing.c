//
// Created by Raphael Bonneval on 1/24/23.
//

#include <sys/fcntl.h>
#include "../../incs/mini_shell.h"

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

void	set_builtin(t_lstd *current)
{
	if (ft_str_cmp(get(current)->cmd[0], "echo")
		|| ft_str_cmp(get(current)->cmd[0], "cd")
		|| ft_str_cmp(get(current)->cmd[0], "pwd")
		|| ft_str_cmp(get(current)->cmd[0], "export")
		|| ft_str_cmp(get(current)->cmd[0], "unset")
		|| ft_str_cmp(get(current)->cmd[0], "env")
		|| ft_str_cmp(get(current)->cmd[0], "exit"))
		get(current)->is_builtin = TRUE;
}

t_error	fill_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_error	status;

	current = ft_lstd_first(ms->cmds);
	dprintf(1, "get_first DONE | ");
	while (current)
	{
		// TODO [Aurel]: find and replace $ARG with env_lst key/value
		status = open_files(ms, get(current));
		dprintf(1, "open_Files DONE | ");
		if (status == MALLOC_ERROR)
			return (MALLOC_ERROR);
		else if (status == ERROR)
			get(current)->is_valid = FALSE;
		if (get_cmd(get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		dprintf(1, "get_cmd DONE | ");
		if (get_path(get(current), ms->env_dict) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		dprintf(1, "get_path DONE | ");
		set_builtin(current);
		current = current->next;
	}
	return (SUCCESS);
}

t_error	parse_line(t_mini_shell *mini_shell, char *line)
{
	if (check_line(line) == ERROR)
		return (ERROR);
	dprintf(1, "check DONE | ");
	if (create_cmds(mini_shell, line) == MALLOC_ERROR)
		return (free(line), exit_malloc(mini_shell));
	dprintf(1, "crete cmds DONE | ");
	if (fill_cmds(mini_shell) == MALLOC_ERROR)
		return (free(line), exit_malloc(mini_shell));
	dprintf(1, "fill cmds DONE\n");
	return (SUCCESS);
}

/// cmp func to not use exept in get_env_value
int find(void *content, void *ref)
{
	if (ft_str_cmp(get_env_dict(content)->key, (char *)ref) == 0)
		return (1);
	return (0);
}

/// interpret the string after $ sign
char *get_env_value(char *key, t_lstd *env_dict)
{
	return (get_env_dict(ft_lstd_find(env_dict, key, find)->content)
		->value[0]);
}

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

