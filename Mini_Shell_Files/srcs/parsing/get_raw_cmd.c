//
// Created by Raphael Bonneval on 1/24/23.
//

#include "../../incs/mini_shell.h"

int	count_blocks(char *line)
{
	char	quote;
	int		block;

	quote = 0;
	block = 0;
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		while (*line && !(!set_quote_state(*line, &quote) && *line == '|'))
			line++;
		line++;
		while (*line && *line == ' ')
			line++;
		block++;
	}
	return (block);
}

t_error	fill_split(char **split, char *line)
{
	char	quote;
	int		len;
	int		block;

	quote = 0;
	block = 0;
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		len = 0;
		while (line[len] && !(!set_quote_state(line[len], &quote) && line[len]
																	 == '|'))
			len++;
		split[block] = ft_substr(line, 0, len);
		if (!split[block])
			return (MALLOC_ERROR);
		line += len + 1;
		while (*line && *line == ' ')
			line++;
		block++;
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
	if (fill_split(split, line) == MALLOC_ERROR)
		return (free_split(split), NULL);
	return (split);
}