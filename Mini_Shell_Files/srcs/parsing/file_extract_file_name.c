#include "../../incs/mini_shell.h"

static t_error	replace_dollar(t_mini_shell *ms, char **str, t_chevron type)
{
	char	*key;
	t_lstd	*dict;

	if (type == HERE_DOC_REDIR)
		return (SUCCESS);
	if (**str && (*str)[1] && **str == '$' && valid_id_dollars((*str)[1]))
	{
		key = (*str) + 1;
		dict = ft_lstd_find(ms->env_dict, key, find_in_dict);
		*str = ft_free(*str);
		if (dict)
			*str = ft_strdup(get_env_dict(dict->content)->value);
		else
			*str = ft_strdup("");
		if (*str == NULL)
			return (MALLOC_ERROR);
		if (ft_contain(*str, ' '))
			return (parse_error(ms, AMBIGUOUS_REDIRECT, 2));
		if (ft_contain(*str, '/'))
			return (parse_error(ms, IS_DIRECTORY, 2));
	}
	return (SUCCESS);
}

char *find_end(char *start)
{
	char	*end;
	char	quote;

	quote = 0;
	end = start;
	while (*end)
	{
		if (quote == 0)
		{
			if (set_quote_state(*end, &quote))
			{
				end++;
				continue;
			}
		}
		set_quote_state(*end, &quote);
		if (!quote && ft_contain("<> ", *end))
			break ;
		if (quote && *end == quote
			&& (ft_contain("<> ", end[1]) || !end[1]))
			break ;
		end++;
	}
	return (end);
}

t_chevron	get_type_here_doc(char *start, char *end, t_chevron type)
{
	if (type != HERE_DOC_REDIR)
		return (type);
	while (start != end)
	{
		if (*start == '\"' || *start == '\'')
			return (HERE_DOC_QUOTE_REDIR);
		start++;
	}
	return (type);
}

t_error	extract_file_name(t_mini_shell *ms, char *str, t_chevron *type,
	char **file_name)
{
	char	*start;
	t_error	replace_status;
	char	quote;

	quote = 0;
	while (*str == ' ')
		str++;
	start = str;
	str = find_end(str);
	*type = get_type_here_doc(start, str, *type);
	*file_name = str_dup_no_quote(start, str - start);
	if (!*file_name)
		return (MALLOC_ERROR);
	replace_status = replace_dollar(ms, file_name, *type);
	if (replace_status != SUCCESS)
		return (replace_status);
	if (*str && *str == quote)
		(*str)++;
	while (*start && start != str)
	{
		*start = ' ';
		start++;
	}
	return (SUCCESS);
}
