/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:35:04 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 19:53:28 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mini_shell.h"
#include <stdlib.h>
#include <stdio.h>

t_error	exit_malloc(t_mini_shell *mini_shell)
{
	printf("The Program was terminated cause of an ERROR of memory "
		"allocation\n");
	free_mini_shell(mini_shell);
	exit(0);
}

t_error	exit_end_program(t_mini_shell *mini_shell)
{
	printf("The Program was terminated normally\n");
	free_mini_shell(mini_shell);
	exit(0);
}