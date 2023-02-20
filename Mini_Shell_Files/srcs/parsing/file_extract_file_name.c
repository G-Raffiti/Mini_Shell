#include "../../incs/mini_shell.h"

static t_error	replace_dollar(t_mini_shell *ms, char **str, t_chevron type)
{
	char	*key;
	t_lstd	*dict;

	if (type == HERE_DOC_REDIR)
		return (SUCCESS);
	if ((*str)[1] && **str == '$' && valid_id_dollars((*str)[1]))
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
			return (free(*str), parse_error(ms, AMBIGUOUS_REDIRECT, 2));
		if (ft_contain(*str, '/'))
			return (free(*str), parse_error(ms, IS_DIRECTORY, 2));
	}
	return (SUCCESS);
}

char	*extract_file_name(t_mini_shell *ms, char *str, char *quote,
						t_chevron type)
{
	char	*file_name;
	char	*start;

	while (*str == ' ')
		str++;
	if (set_quote_state(*str, quote))
		str++;
	start = str;
	while (*str && (!ft_contain(" <>\"\'", *str)
			|| (*quote && ft_contain("<>", *str))))
		str++;
	file_name = ft_substr(start, 0, str - start);
	if (!file_name)
		return (NULL);
	if (replace_dollar(ms, &file_name, type) == MALLOC_ERROR)
		return (ft_free(file_name));
	if (*str && *str == *quote)
		(*str)++;
	while (*start && start != str)
	{
		*start = ' ';
		start++;
	}
	return (file_name);
}
