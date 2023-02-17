
#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>
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
	else
		cmd->output->fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	cmd->output->name = file_name;
	if (cmd->output->fd == -1)
	{
		cmd->output->error = errno;
		cmd->is_valid = FALSE;
	}
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
	cmd->input->name = file_name;
	if (cmd->input->fd == -1)
	{
		cmd->input->error = errno;
		cmd->is_valid = FALSE;
	}
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

static void	replace_dollar(t_mini_shell *ms, char **str)
{
	char *key;
	t_lstd *dict;

	if ((*str)[1] && **str == '$' && valid_id_dollars((*str)[1]))
	{
		key = (*str) + 1;
		dict = ft_lstd_find(ms->env_dict, key, find_in_dict);
		*str = ft_free(*str);
		if (dict)
			*str = ft_strdup(get_env_dict(dict->content)->value);
		else
			*str = ft_strdup("");
	}
}
static t_error extract_file_name(t_mini_shell *ms, char *str, char *quote, char
**file_name)
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
	// TODO if file name start with a $ replace than check if it contains '
	//  ' or '/' error "ambiguous redirect" and "Is a directory"
	*file_name = ft_substr(start, 0, str - start);
	replace_dollar(ms, file_name);
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
			error = extract_file_name(ms, str, &quote, &file_name);
			if (error != SUCCESS)
				return (error);
			chevron_in(ms, cmd, chevron_type, file_name);
		}
		str++;
	}
	return (error);
}