//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../incs/mini_shell.h"

static int	count_blocks(char *line)
{
	char	quote;
	int		len;
	int		cmd;

	quote = 0;
	cmd = 1;
	while (*line)
	{
		while (*line && !set_quote_state(*line, &quote) && ft_contain("| ",
																	  *line))
			line++;
		if (!*line)
			break ;
		len = 0;
		while (line[len]
			   && (set_quote_state(line[len], &quote) || line[len] != '|'))
			len++;
		line += len;
		cmd++;
	}
	return (cmd);
}

static t_error	fill_split(char **split, char *line, int cmd_nb)
{
	char	quote;
	int		len;
	int		cmd;

	quote = 0;
	cmd = 0;
	while (*line)
	{
		while (*line && !set_quote_state(*line, &quote) && ft_contain("| ",
																	  *line))
			line++;
		if (!*line)
			return (SUCCESS);
		len = 0;
		while (line[len]
			   && (set_quote_state(line[len], &quote) || line[len] != '|'))
			len++;
		split[cmd] = ft_substr(line, 0, len);
		if (!split[cmd])
			return (MALLOC_ERROR);
		line += len;
		cmd++;
	}
	return (SUCCESS);
}

///Split the line where the pipes are;
char	**split_pipe(char *line)
{
	char	**split;
	int		cmd_nb;

	cmd_nb = count_blocks(line);
	split = malloc(sizeof(char *) * (cmd_nb + 1));
	if (!split)
		return (NULL);
	split[cmd_nb] = 0;
	if (fill_split(split, line, cmd_nb) == MALLOC_ERROR)
		return (free_split(split), NULL);
	return (split);
}