#include "../../incs/mini_shell.h"

static int	count_blocks(char *line)
{
	char	quote;
	int		block;

	quote = 0;
	block = 0;
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		while (*line && !(!set_quote_state(*line, &quote) && *line == ' '))
			line++;
		while (*line && *line == ' ')
			line++;
		block++;
	}
	return (block);
}

static t_error	fill_split(char **split, char *line)
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
				== ' '))
			len++;
		split[block] = str_dup_no_quote(line, len);
		if (!split[block])
			return (MALLOC_ERROR);
		line += len;
		while (*line && *line == ' ')
			line++;
		block++;
	}
	return (SUCCESS);
}

///Split the raw_cmd on the quote and spaces
static char	**split_cmd(char *raw_cmd)
{
	char	**split;
	int		cmd_nb;

	cmd_nb = count_blocks(raw_cmd);
	split = ft_calloc(cmd_nb + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (fill_split(split, raw_cmd) == MALLOC_ERROR)
		return (free_split(split), NULL);
	split[cmd_nb] = NULL;
	return (split);
}

t_error	get_cmd(t_cmd *cmd)
{
	if (is_empty_line(cmd->raw_cmd))
	{
		cmd->cmd = NULL;
		return (SUCCESS);
	}
	cmd->cmd = split_cmd(cmd->raw_cmd);
	if (!cmd->cmd)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
