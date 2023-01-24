//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../incs/mini_shell.h"

t_error	parse_line(t_mini_shell *mini_shell, char *line)
{
	int		i;
	char **raw_cmds;
	t_lstd *current;
	t_cmd *cmd;

	// TODO [Raffi]: quote error check
	raw_cmds = split_pipe(line);
	i = 0;
	while(raw_cmds[i])
	{
		if(new_cmd(cmd) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		cmd->raw_cmd = ft_strdup(raw_cmds[i]);
		current = ft_lstd_new(cmd);
		ft_lstd_push_back_elem(&mini_shell->cmds, current);
		i++;
	}
	raw_cmds = free_split(raw_cmds);

	// in the list
	// TODO [Aurel]: find and replace $ARG with env_lst key/value
	// TODO [Raffi]: open all fds t_cmd + chevron
	// TODO [Raffi]: get_cmd() -> char** + get_args_cmd()
	// TODO [Raffi]: get_path() + access
	// TODO [Raffi]: set_is_builtin() strcmp cmd[0] -> builtin lst

	return (SUCCESS);
}

///Split the line whenre the pipes are;
char **split_pipe(char *line)
{
	// TODO []: Call the quote state func
	char	**split;
	t_bool	in_quote;
	int cmd_nb;

	in_quote = 0;
	cmd_nb = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			in_quote = !in_quote;
		if (*line == '|' && !in_quote)
			cmd_nb++;
	}
}

/// cmp func to not use exept in get_env
int find(void *content, void *ref)
{
	if (ft_str_cmp(get_arg_env(content)->key, (char *)ref) == 0)
		return (1);
	return (0);
}

/// interpret the string after $ sign
char *get_env(char *arg_name, t_lstd *args_env)
{
	return (get_arg_env(ft_lstd_find(args_env, arg_name, find)->content)
		->value[0]);
}

/// TO use every where
int	quote_state(char c, char *quote)
{
	if (c == *quote && *quote != 0)
		*quote = 0;
	else if (*quote == 0 && c == '\'')
		*quote = 1;
	else if (*quote == 0 && c == '\"')
		*quote = 2;
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

char	**get_cmd(char *block, int start, int end)
{

}