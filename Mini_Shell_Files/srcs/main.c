/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:13:58 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/24 12:42:39 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incs/mini_shell.h"

int g_exit_code;

t_error parse_input(t_mini_shell *mini_shell)
{
	ft_lstd_clear(&mini_shell->cmds, (void(*)(void *))free_cmd);
	create_new_list(&mini_shell->cmds);
	return (SUCCESS);
}

static void	loop(t_mini_shell *mini_shell)
{
	char	*line;

	while (TRUE)
	{
		clear_input(mini_shell);
		line = read_line();
		if (!line)
			return ;
		if (parse_line(mini_shell, line) == ERROR)
			return ;

	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	mini_shell;

	printf("Hello Hell !\n");
	if (new_mini_shell(&mini_shell) == MALLOC_ERROR)
		exit_malloc(&mini_shell);
	initialize_mini_shell(&mini_shell, argc, argv, env);
	loop(&mini_shell);
	exit_end_program(&mini_shell);
}
