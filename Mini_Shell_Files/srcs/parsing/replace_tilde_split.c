#include "../../incs/mini_shell.h"

int	count_part_tilde(char *raw)
{
	int		part;
	char	quote;
	int		i;

	part = 1;
	quote = 0;
	i = -1;
	while (raw[++i])
	{
		if (set_quote_state(raw[i], &quote) == 0
			&& raw[i] == ' '
			&& (raw[i + 1] == '~')
			&& (!raw[i + 2] || raw[i + 2] == '/' || raw[i + 2] == ' '))
			part++;
	}
	return (part);
}

static t_bool	is_valid_tilde(const char *raw, char *quote, int i)
{
	return (!raw[i + 1]
		|| (set_quote_state(raw[i], quote) == 0
			&& raw[i] == ' '
			&& (raw[i + 1] == '~')
			&& (!raw[i + 2]
				|| raw[i + 2] == '/'
				|| raw[i + 2] == ' ')));
}

t_error	fill_split_tilde(char **split, char *raw)
{
	int		len;
	char	quote;
	int		i;
	int		part;
	char	*start;

	len = 0;
	quote = 0;
	i = -1;
	part = 0;
	start = raw;
	while (raw[++i])
	{
		len++;
		if (is_valid_tilde(raw, &quote, i))
		{
			split[part] = ft_substr(start, 0, len);
			if (split[part] == NULL)
				return (MALLOC_ERROR);
			len = 0;
			part++;
			start = &raw[i + 1];
		}
	}
	return (SUCCESS);
}
