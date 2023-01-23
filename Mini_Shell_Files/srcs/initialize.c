/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:32:47 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 19:53:28 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mini_shell.h"

void	initialize_mini_shell(t_mini_shell *mini_shell, int argc, char \
	**argv, char **env)
{
	mini_shell->env = env;
	(void)argc;
	(void)argv;
}