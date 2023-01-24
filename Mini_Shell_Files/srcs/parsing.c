//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../incs/mini_shell.h"
t_bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (TRUE);
		line++;
	}
	return (FALSE);
}

t_bool	is_quote_error(char *line)
{
	char	quote_state;

	quote_state = 0;
	while (*line)
	{
		set_quote_state(*line, &quote_state);
		line++;
	}
	if (quote_state > 0)
		return (FALSE);
	return (TRUE);
}

t_bool	is_chevron_error(char *line)
{
	t_bool	is_chevron_last;
	char	is_in_quote;

	is_in_quote = 0;
	while (*line)
	{
		set_quote_state(*line, &is_in_quote);
		if (!is_chevron_last && !is_in_quote && ft_contain("<>", *line))
			is_chevron_last = TRUE;
		else if (is_chevron_last && *line != ' ')
			is_chevron_last = FALSE;
		line++;
	}
	return (!is_chevron_last);
}

t_error	parse_error(char *error_msg, int error_code)
{
	g_exit_code = error_code;
	printf("%s", error_msg);
	return (ERROR);
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
		if(new_cmd(cmd) == MALLOC_ERROR)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds),
					MALLOC_ERROR);
		cmd->raw_cmd = ft_strdup(raw_cmds[i]);
		if (!cmd->raw_cmd)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds),
					MALLOC_ERROR);
		current = ft_lstd_new(cmd);
		if (!current)
			return (free_split(raw_cmds), clear_cmds(&mini_shell->cmds),
					MALLOC_ERROR);
		ft_lstd_push_back_elem(&mini_shell->cmds, current);
		i++;
	}
	raw_cmds = free_split(raw_cmds);
	return (SUCCESS);
}

t_error	get_path(t_lstd *current, t_lstd *env_dict)
{
	char **paths;

	if (access(get(current)->cmd[0], X_OK) == 0)
	{
		get(current)->path = ft_strdup(get(current)->cmd[0]);
		if (!get(current)->path)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	paths = get_env_dict(ft_lstd_find(env_dict, "PATH", find)->content)->value;
	while (paths)
	{
		get(current)->path = ft_strjoin(paths[0], get(current)->cmd[0]);
		if (!get(current)->path)
			return (MALLOC_ERROR);
		if (access(get(current)->path, X_OK) == 0)
			return (SUCCESS);
		get(current)->path = ft_free(get(current)->path);
		paths++;
	}
	return (SUCCESS);
}

t_error	get_cmd(t_lstd *current)
{
	get(current)->cmd = split_cmd(get(current)->raw_cmd);
	if (!get(current)->cmd)
		return (MALLOC_ERROR);
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

t_error	fill_cmds(t_mini_shell *mini_shell)
{
	t_lstd	*current;

	current = ft_lstd_first(mini_shell->cmds);
	while (current)
	{
		// TODO [Aurel]: find and replace $ARG with env_lst key/value
		// TODO [Raffi]: open all fds t_cmd + chevron
		// TODO [Raffi]: get_cmd() -> char** + get_args_cmd()
		if (get_cmd(current) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (get_path(current, mini_shell->env_dict) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		set_builtin(current);
		current = current->next;
	}
	return (SUCCESS);
}

t_error	parse_line(t_mini_shell *mini_shell, char *line)
{
	if (is_empty_line(line))
		return (parse_error("", 127));
	if (is_quote_error(line))
		return (parse_error("command not parsed due to quotes\n", 0));
	if (is_chevron_error(line))
		return (parse_error("syntax error near unexpected token `newline'\n",
							258));
	if (create_cmds(mini_shell, line) == MALLOC_ERROR)
		return (free(line), exit_malloc(mini_shell));
	if (fill_cmds(mini_shell) == MALLOC_ERROR)
		return (free(line), exit_malloc(mini_shell));
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
		*quote = 1;
	else if (*quote == 0 && c == '\"')
		*quote = 2;
	return (*quote);
}


///open file and create t_fd
t_fd	*chevron(t_lstd *current, char *file_path, char *chevron_type)
{
	if (ft_str_cmp("<", chevron_type) == 0)
	{

	}

	if (ft_str_cmp("<<", chevron_type) == 0)
	{

	}

	if (ft_str_cmp(">", chevron_type) == 0)
	{

	}

	if (ft_str_cmp(">>", chevron_type) == 0)
	{

	}
}