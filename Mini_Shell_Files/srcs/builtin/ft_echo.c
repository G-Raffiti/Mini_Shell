/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:26 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 14:00:26 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_bool	is_n(char *str)
{
	if (!str[0] || (str[0] && str[0] != '-' && (!str[1] || str[1] != 'n')))
		return (FALSE);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_error	ft_echo(t_cmd *cmd)
{
	t_bool	newline;
	char	**split;
	char	*str;

	newline = TRUE;
	split = &cmd->cmd[1];
	while (*split && is_n(*split))
	{
		split++;
		newline = FALSE;
	}
	str = ft_strjoin_split(split, " ");
	if (!str)
		return (MALLOC_ERROR);
	if (newline)
		printf("%s\n", str);
	else
		printf("%s", str);
	str = ft_free(str);
	set_exit_code(EXIT_SUCCESS);
	return (SUCCESS);
}
