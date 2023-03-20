/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:47 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:58:47 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (FALSE);
		line++;
	}
	return (TRUE);
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
	if (quote_state != 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_pipe_error(char *line)
{
	t_bool	is_pipe_last;
	char	is_in_quote;

	is_in_quote = 0;
	is_pipe_last = FALSE;
	while (*line && *line == ' ')
		line++;
	if (*line == '|')
		return (TRUE);
	while (*line)
	{
		set_quote_state(*line, &is_in_quote);
		if (!is_pipe_last && !is_in_quote && *line == '|')
			is_pipe_last = TRUE;
		else if (is_pipe_last && *line != ' ')
			is_pipe_last = FALSE;
		line++;
	}
	return (is_pipe_last);
}

t_bool	is_chevron_error(char *line)
{
	t_bool	is_chevron_last;
	char	is_in_quote;

	is_in_quote = 0;
	is_chevron_last = FALSE;
	while (*line)
	{
		set_quote_state(*line, &is_in_quote);
		if (!is_chevron_last && !is_in_quote && ft_contain("<>", *line))
			is_chevron_last = TRUE;
		else if (is_chevron_last && *line == '|')
			return (TRUE);
		else if (is_chevron_last && *line != ' ')
			is_chevron_last = FALSE;
		line++;
	}
	return (FALSE);
}

t_error	check_line(t_mini_shell *ms, char *line)
{
	if (is_pipe_error(line))
		return (parse_error(ms, SYNTAX_PIPE, 2));
	if (is_quote_error(line))
		return (parse_error(ms, QUOTE_ERROR, 2));
	if (is_chevron_error(line))
		return (parse_error(ms, SYNTAX_PIPE, 2));
	return (SUCCESS);
}
