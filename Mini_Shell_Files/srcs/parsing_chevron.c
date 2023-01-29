/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 06:06:58 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/29 06:06:58 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/fcntl.h>
#include "../incs/mini_shell.h"
static void	chevron_in(t_lstd *current, t_chevron type, char *file_name);
static void	chevron_out(t_lstd *current, t_chevron type, char *file_name);

///open file and create t_fd
static void	chevron_in(t_lstd *current, t_chevron type, char *file_name)
{
	if (!get(current)->is_valid)
		return ;
	if (type == OUT_CHT || type == APPEND_CHT)
		chevron_out(current, type, file_name);
	if (get(current)->input->fd != -1)
		close(get(current)->input->fd);
	if (type == IN_CHT)
	{
		get(current)->input->fd = open(file_name, O_RDONLY);
	}
	else if (type == HERE_DOC_CHT)
	{
		// TODO [Raffi] : find the here_doc open mod
		get(current)->input->fd = open(file_name, O_RDONLY);
	}
	if (get(current)->input->fd == -1)
	{
		perror(file_name);
		get(current)->is_valid = FALSE;
	}
}

///open file and create t_fd
static void	chevron_out(t_lstd *current, t_chevron type, char *file_name)
{
	if (get(current)->output->fd != -1)
		close(get(current)->output->fd);
	if (type == OUT_CHT)
	{
		get(current)->output->fd = open(file_name, O_CREAT | O_WRONLY
												   | O_TRUNC, 0644);
	}
	else if (type == APPEND_CHT)
	{
		get(current)->output->fd = open(file_name, O_CREAT | O_WRONLY
												   | O_APPEND, 0644);
	}
	if (get(current)->input->fd == -1)
	{
		perror(file_name);
		get(current)->is_valid = FALSE;
	}
}

static t_chevron get_chevron_type(char **str)
{
	t_chevron	type;

	if (**str == '<' && **(str + 1) != '<')
		type = IN_CHT;
	else if (**str == '>' && **(str + 1) != '>')
		type = OUT_CHT;
	else if (**str == '<' && **(str + 1) == '<')
	{
		type = HERE_DOC_CHT;
		(*str)++;
	}
	else if (**str == '>' && **(str + 1) != '>')
	{
		type = APPEND_CHT;
		(*str)++;
	}
	(*str)++;
	return (type);
}

static t_error extract_file_name(char **str, char *quote, char **file_name)
{
	char	*start;

	while (**str == ' ')
		*str++;
	if (set_quote_state(**str, quote))
		*str++;
	start = *str;
	if (**str == '<' || **str == '>')
		return (ERROR);
	while (**str && (!ft_contain(" <>\"\'", **str)
					|| quote && ft_contain("<>", **str)))
		*str++;
	*file_name = ft_substr(start, 0, *str - start);
	if (!*file_name)
		return (MALLOC_ERROR);
	if (**str && **str == *quote)
		*str++;
	while (*start && start != *str)
	{
		*start = ' ';
		start++;
	}
	return (SUCCESS);
}

t_error	open_files(t_lstd *current)
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
			chevron_type = get_chevron_type(&str);
			error = extract_file_name(&str, &quote, &file_name);
			if (error != SUCCESS)
				return (error);
			chevron_in(current, chevron_type, file_name);
			file_name = ft_free(file_name);
		}
	}
	return (error);
}