#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>
#include "../../incs/mini_shell.h"

///open file and create t_fd
static void	chevron_out(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	cmd->output->type = type;
	if (cmd->output->fd > 0)
	{
		safe_close(ms, cmd->output->fd, "chevron_out");
		cmd->output->name = ft_free(cmd->output->name);
	}
	if (type == OUT_REDIR)
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	cmd->output->name = file_name;
	if (cmd->output->fd == -1)
		cmd->output->error = errno;
}

static void	chevron_in(t_mini_shell *ms, t_cmd *cmd, t_chevron type, char
*file_name)
{
	if (cmd->input->fd == -1)
		return ;
	cmd->input->type = type;
	if (type == OUT_REDIR || type == APPEND_REDIR)
	{
		chevron_out(ms, cmd, type, file_name);
		return ;
	}
	if (cmd->input->fd > 0)
	{
		safe_close(ms, cmd->input->fd, "chevron_in");
		cmd->input->name = ft_free(cmd->input->name);
	}
	if (type == IN_REDIR)
		cmd->input->fd = open(file_name, O_RDONLY);
	else if (type == HERE_DOC_REDIR)
	{
		safe_pipe(ms, cmd->input->here_doc_pipe, "chevron_in");
		cmd->input->fd = cmd->input->here_doc_pipe[0];
		cmd->input->limiter = file_name;
	}
	cmd->input->name = file_name;
	if (cmd->input->fd == -1)
		cmd->input->error = errno;
}

static t_chevron	get_chevron_type(char *str)
{
	t_chevron	type;

	type = -1;
	if (*str == '<' && *(str + 1) != '<')
		type = IN_REDIR;
	else if (*str == '>' && *(str + 1) != '>')
		type = OUT_REDIR;
	else if (*str == '<' && *(str + 1) == '<')
	{
		type = HERE_DOC_REDIR;
		*str = ' ';
		str++;
	}
	else if (*str == '>' && *(str + 1) == '>')
	{
		type = APPEND_REDIR;
		*str = ' ';
		str++;
	}
	*str = ' ';
	return (type);
}

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
			file_name = extract_file_name(ms, str, &quote, chevron_type);
			if (file_name == NULL)
				return (MALLOC_ERROR);
			chevron_in(ms, cmd, chevron_type, file_name);
		}
		str++;
	}
	return (error);
}
