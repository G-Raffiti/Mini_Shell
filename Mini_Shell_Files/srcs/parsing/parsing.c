/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:06 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:58:06 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

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

t_error	create_cmds(t_mini_shell *mini_shell, char **raw_cmds)
{
	int		i;
	t_lstd	*current;
	t_cmd	*cmd;

	i = 0;
	while (raw_cmds[i])
	{
		if (new_cmd(&cmd) == MALLOC_ERROR)
			return (free_split(raw_cmds),
				clear_cmds(&mini_shell->cmds, free_cmd), MALLOC_ERROR);
		cmd->raw_cmd = ft_strdup(raw_cmds[i]);
		if (!cmd->raw_cmd)
			return (free_split(raw_cmds),
				clear_cmds(&mini_shell->cmds, free_cmd), MALLOC_ERROR);
		current = ft_lstd_new(cmd);
		if (!current)
			return (free_split(raw_cmds),
				clear_cmds(&mini_shell->cmds, free_cmd), MALLOC_ERROR);
		ft_lstd_push_back_elem(&mini_shell->cmds, current);
		i++;
	}
	raw_cmds = free_split(raw_cmds);
	return (SUCCESS);
}

t_bool	need_path(t_lstd *current)
{
	return (get(current)->cmd && !get(current)->is_builtin);
}

t_error	fill_cmds(t_mini_shell *ms)
{
	t_lstd	*current;
	t_error	is_open_possible;

	current = ft_lstd_first(ms->cmds);
	while (current)
	{
		if (is_empty_line(get(current)->raw_cmd))
			return (parse_error(ms, SYNTAX_PIPE, 2));
		is_open_possible = open_files(ms, get(current));
		if (is_open_possible != SUCCESS)
			return (is_open_possible);
		if (replace_tilde(ms, get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		replace_dollar_before_quotes(get(current));
		if (replace_dollars(ms, get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (get_cmd(get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		set_builtin(get(current));
		if (need_path(current) && get_path(ms, get(current)) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		current = current->next;
	}
	return (SUCCESS);
}

t_error	parse_line(t_mini_shell *ms, char *line)
{
	t_error	status;
	char	**raw_cmds;

	if (check_line(ms, line) == ERROR)
		return (ERROR);
	raw_cmds = split_pipe(line);
	if (!raw_cmds)
		return (MALLOC_ERROR);
	if (create_cmds(ms, raw_cmds) == MALLOC_ERROR)
		return (free(line), exit_malloc(ms, "parsing: crete_cmds"));
	status = fill_cmds(ms);
	if (status == MALLOC_ERROR)
		return (free(line), exit_malloc(ms, "parsing: fill_cmds"));
	else if (status == ERROR)
		return (ERROR);
	return (SUCCESS);
}
