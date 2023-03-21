/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:54 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:57:54 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../incs/mini_shell.h"

char	*read_line(void)
{
	char	*line;

	set_interactiv_signals();
	line = readline(PROMPT"-▶ "WHITE);
	if (line && ft_strlen(line) > 0 && !is_empty_line(line))
		add_history(line);
	return (line);
}
