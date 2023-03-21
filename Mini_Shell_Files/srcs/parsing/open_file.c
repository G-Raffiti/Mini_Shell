/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:34:37 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 15:43:30 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Lib_List_Double/incs/ft_lstd.h"
#include "../../incs/mini_shell.h"

t_error	valid_file(t_mini_shell *ms, char *str)
{
	while (*str == ' ')
		str++;
	if (ft_strncmp(str, "<<<", 3) == 0)
		return (parse_error(ms, SYNTAX_REDIR_3IN, 2));
	if (ft_strncmp(str, "<<", 2) == 0)
		return (parse_error(ms, SYNTAX_REDIR_2IN, 2));
	if (ft_strncmp(str, ">>", 2) == 0)
		return (parse_error(ms, SYNTAX_REDIR_2OUT, 2));
	if (*str == '<')
		return (parse_error(ms, SYNTAX_REDIR_IN, 2));
	if (*str == '>')
		return (parse_error(ms, SYNTAX_REDIR_OUT, 2));
	if (*str == '|')
		return (parse_error(ms, SYNTAX_PIPE, 2));
	if (!*str)
		return (parse_error(ms, SYNTAX_NEWLINE, 2));
	return (SUCCESS);
}

t_error	open_files(t_mini_shell *ms, t_cmd *cmd)
{
	char		*str;
	char		quote;
	char		*file_name;
	t_chevron	chevron_type;
	t_error		error;

	error = SUCCESS;
	str = cmd->raw_cmd;
	quote = 0;
	while (*str)
	{
		if (!set_quote_state(*str, &quote) && ft_contain("<>", *str))
		{
			chevron_type = get_chevron_type(str);
			if (valid_file(ms, str) == ERROR)
				return (ERROR);
			error = extract_file_name(ms, str, &chevron_type, &file_name);
			if (error != SUCCESS)
				return (file_name = ft_free(file_name), error);
			if (chevron_in(ms, cmd, chevron_type, file_name) == MALLOC_ERROR)
				return (file_name = ft_free(file_name), MALLOC_ERROR);
		}
		str++;
	}
	return (error);
}