/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:13:58 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 18:45:06 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incs/mini_shell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini_shell	mini_shell;

	if (new_mini_shell(&mini_shell) == MALLOC_ERROR)
		exit_malloc(&mini_shell);
	initialize_mini_shell(&mini_shell, argc, argv, env);

	exit_end_program(&mini_shell);
	printf("Hello Hell !");
}