/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:31 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 14:00:31 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	ft_env(t_mini_shell *ms)
{
	int	i;

	i = -1;
	while (ms->env && ms->env[++i])
		printf("%s\n", ms->env[i]);
	set_exit_code(EXIT_SUCCESS);
	return (SUCCESS);
}
