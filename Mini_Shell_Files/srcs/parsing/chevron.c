
#include <sys/fcntl.h>
#include "../../incs/mini_shell.h"

///open file and create t_fd
static void	chevron_out(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	if (cmd->output->fd > 0)
	{
		safe_close(ms, cmd->output->fd, "chevron_out");
		cmd->output->name = ft_free(cmd->input->name);
	}
	if (type == OUT_CHT)
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else // if (type == APPEND_CHT)
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	cmd->output->type = type;
	cmd->output->name = file_name;
	if (cmd->output->fd == -1)
	{
		perror(file_name);
		ft_free(file_name);
		cmd->is_valid = FALSE;
	}
	printf("{out: %d-%s} ", cmd->output->fd, file_name);
}

///open file and create t_fd
static void	chevron_in(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	if (!cmd->is_valid)
		return ;
	if (type == OUT_CHT || type == APPEND_CHT)
	{
		chevron_out(ms, cmd, type, file_name);
		return ;
	}
	if (cmd->input->fd > 0)
	{
		safe_close(ms, cmd->input->fd, "chevron_in");
		cmd->input->name = ft_free(cmd->input->name);
	}
	if (type == IN_CHT)
		cmd->input->fd = open(file_name, O_RDONLY);
	else if (type == HERE_DOC_CHT)
		cmd->input->fd = open(file_name, O_CREAT | O_TRUNC |
		O_WRONLY, 0644);
	cmd->input->type = type;
	cmd->input->name = file_name;
	if (cmd->input->fd == -1)
	{
		perror(file_name);
		ft_free(file_name);
		cmd->is_valid = FALSE;
	}
	printf("{in: %d-%s} ", cmd->input->fd, file_name);
}


static t_chevron get_chevron_type(char *str)
{
	t_chevron	type;

	type = -1;
	if (*str == '<' && *(str + 1) != '<')
		type = IN_CHT;
	else if (*str == '>' && *(str + 1) != '>')
		type = OUT_CHT;
	else if (*str == '<' && *(str + 1) == '<')
	{
		type = HERE_DOC_CHT;
		*str = ' ';
		str++;
	}
	else if (*str == '>' && *(str + 1) == '>')
	{
		type = APPEND_CHT;
		*str = ' ';
		str++;
	}
	*str = ' ';
	return (type);
}

static t_error extract_file_name(char *str, char *quote, char **file_name)
{
	char	*start;

	while (*str == ' ')
		str++;
	if (set_quote_state(*str, quote))
		str++;
	start = str;
	if (!*quote && (*str == '<' || *str == '>'))
		return (ERROR);
	while (*str && (!ft_contain(" <>\"\'", *str)
					|| (*quote && ft_contain("<>", *str))))
		str++;
	*file_name = ft_substr(start, 0, str - start);
	if (!*file_name)
		return (MALLOC_ERROR);
	if (*str && *str == *quote)
		(*str)++;
	while (*start && start != str)
	{
		*start = ' ';
		start++;
	}
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
			if (extract_file_name(str, &quote, &file_name) != SUCCESS)
				return (error);
			chevron_in(ms, cmd, chevron_type, file_name);
		}
		str++;
	}
	return (error);
}