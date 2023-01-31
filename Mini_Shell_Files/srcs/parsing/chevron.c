
#include <sys/fcntl.h>
#include "../../incs/mini_shell.h"

///open file and create t_fd
static void	chevron_out(t_mini_shell *ms, t_lstd *current, t_chevron type, char
*file_name)
{
	if (get(current)->output->fd != -1)
		safe_close(ms, get(current)->output, "chevron_out");
	if (type == OUT_CHT)
	{
		get(current)->output->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		get(current)->output->type = type;
	}
	else // if (type == APPEND_CHT)
	{
		get(current)->output->fd = open(file_name, O_CREAT | O_WRONLY
												   | O_APPEND, 0644);
		get(current)->output->type = type;
	}
	printf("{out: %d-%s} ", get(current)->output->fd, file_name);
	if (get(current)->output->fd == -1)
	{
		perror(file_name);
		get(current)->is_valid = FALSE;
	}

}

///open file and create t_fd
static void	chevron_in(t_mini_shell *ms, t_lstd *current, t_chevron type, char
*file_name)
{
	if (!get(current)->is_valid)
		return ;
	if (type == OUT_CHT || type == APPEND_CHT)
	{
		chevron_out(ms, current, type, file_name);
		return ;
	}
	safe_close(ms, get(current)->input, "chevron_in");//TODO casseur de open
	if (type == IN_CHT)
	{
		get(current)->input->fd = open(file_name, O_RDONLY);
		//dprintf(2,"ok %d-%s\n", get(current)->input->fd, file_name);
		get(current)->input->type = type;
	}
	else if (type == HERE_DOC_CHT)
	{
		get(current)->input->fd = open(file_name, O_CREAT | O_TRUNC |
		O_WRONLY, 0644);
		get(current)->input->type = type;
	}
	printf("{in: %d-%s} ", get(current)->input->fd, file_name);
	if (get(current)->input->fd == -1)
	{
		perror(file_name);
		get(current)->is_valid = FALSE;
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

t_error	open_files(t_mini_shell *ms, t_lstd *current)
{
	char		*str;
	char		quote;
	char		*file_name;
	t_chevron	chevron_type;
	t_error		error;

	error = SUCCESS;
	str = get(current)->raw_cmd;
	quote = 0;
	while (*str)
	{
		if (!set_quote_state(*str, &quote) && ft_contain("<>", *str))
		{
			chevron_type = get_chevron_type(str);
			if (extract_file_name(str, &quote, &file_name) != SUCCESS)
				return (error);
			chevron_in(ms, current, chevron_type, file_name);
			file_name = ft_free(file_name);
		}
		str++;
	}
	return (error);
}