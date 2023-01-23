/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:13:58 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 19:53:28 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incs/mini_shell.h"

t_error parse_input(t_mini_shell *mini_shell)
{
	ft_lstd_clear(&mini_shell->cmds, (void(*)(void *))free_cmd);
	create_new_list(&mini_shell->cmds);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	mini_shell;

	if (new_mini_shell(&mini_shell) == MALLOC_ERROR)
		exit_malloc(&mini_shell);
	initialize_mini_shell(&mini_shell, argc, argv, env);

	while (mini_shell)
	{
		if (parse_input(&mini_shell) != SUCCESS)
		{
			clear_input(mini_shell);
			print_error(mini_shell);
		}
		else
		{
			exec_cmds(mini_shell);
		}
	}
	exit_end_program(&mini_shell);
	printf("Hello Hell !");
}