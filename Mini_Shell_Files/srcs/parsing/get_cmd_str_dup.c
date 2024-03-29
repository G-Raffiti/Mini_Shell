/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_str_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:25 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:58:25 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

size_t	block_len(char *line, size_t len)
{
	size_t	i;
	char	quote;
	size_t	count;

	i = 0;
	quote = 0;
	count = 0;
	while (i < len)
	{
		set_quote_state(line[i], &quote);
		if (line[i] == quote || (!quote && (line[i] == '\"' || line[i]
					== '\'')))
			count++;
		i++;
	}
	return (i - count);
}

char	*str_dup_no_quote(char *line, size_t len)
{
	char	*dup;
	char	quote;
	size_t	i;

	len = block_len(line, len);
	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	quote = 0;
	while (line[i] && i < len)
	{
		set_quote_state(line[i], &quote);
		if ((line[i] == quote || (!quote && (line[i] == '\"'
						|| line[i] == '\''))))
			line++;
		else
		{
			dup[i] = line[i];
			i++;
		}
	}
	return (dup);
}
