//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../incs/mini_shell.h"

static int	count_blocks(char *line)
{
	char	quote;
	int		block;

	quote = 0;
	block = 1;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (!*line)
			break ;
		set_quote_state(*line, &quote);
		block++;
		if (quote)
			while (*line && *line != quote)
				line++;
		else
			while (*line && !set_quote_state(*line, &quote) && *line != ' ')
				line++;
	}
	return (block);
}

static int	count_len(char *line, char quote)
{
	int		len;

	len = 0;
	if (quote)
	{
		line++;
		len++;
		while (*line && *line != quote)
		{
			line++;
			len++;
		}
	}
	else
	{
		while (*line && !set_quote_state(*line, &quote) && *line != ' ')
		{
			line++;
			len++;
		}
	}
	return (len);
}

static t_error	fill_split(char **split, char *line)
{
	char	quote;
	int		len;
	int		block;

	quote = 0;
	block = 0;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (!*line)
			break ;
		set_quote_state(*line, &quote);
		len = count_len(line, quote);
		split[block] = ft_substr(line, 0, len);
		if (!split[block])
			return (MALLOC_ERROR);
		line += len;
		block++;
	}
	return (SUCCESS);
}

///Split the raw_cmd on the quote and spaces
char	**split_cmd(char *raw_cmd)
{
	char	**split;
	int		cmd_nb;

	cmd_nb = count_blocks(raw_cmd);
	split = malloc(sizeof(char *) * (cmd_nb + 1));
	if (!split)
		return (NULL);
	split[cmd_nb] = 0;
	if (fill_split(split, raw_cmd) == MALLOC_ERROR)
		return (free_split(split), NULL);
	return (split);
}