//
// Created by rbonneva on 30/01/23.
//

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
		else if (is_chevron_last && *line != ' ')
			is_chevron_last = FALSE;
		line++;
	}
	return (is_chevron_last);
}

t_error	parse_error(char *error_msg, int error_code)
{
	set_exit_code(error_code);
	printf("%s", error_msg);
	return (ERROR);
}

t_error	check_line(char *line)
{
	if (is_empty_line(line))
		return (parse_error("empty line\n", 127));
	if (is_quote_error(line))
		return (parse_error("quotes error\n", 0));
	if (is_chevron_error(line))
		return (parse_error("syntax error near unexpected is_dollar `newline'\n",
							258));
	return (SUCCESS);
}
