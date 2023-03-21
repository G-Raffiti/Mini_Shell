/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:00:31 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/21 20:49:31 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

static void	display_export_without_quote(const char *str)
{
	int	j;

	write(1, "declare -x ", 11);
	j = 10;
	while (str[++j] != '=')
		write(1, &str[j], 1);
	write(1, &str[j], 2);
	j += 2;
	while (str[++j + 2])
		write(1, &str[j], 1);
	write(1, "\"\n", 2);
}

void	display_export(t_mini_shell *ms)
{
	int	i;
	int j;
	char *str;

	i = 0;
	while (ms->env_sort[i])
	{
		str = ms->env_sort[i];
		j = 0;
		while (str[j] && str[j] != '\"')
			j++;
		if (str[j + 1] != '\"' && str[j + 1] != '\'')
			printf("%s\n", ms->env_sort[i]);
		else
			display_export_without_quote(str);
		i++;
	}
}

static void	display_env_without_quote(const char *str)
{
	int	j;

	j = -1;
	while (str[++j] != '=')
		write(1, &str[j], 1);
	write(1, &str[j], 1);
	j++;
	while (str[++j + 1])
		write(1, &str[j], 1);
	write(1, "\n", 2);
}

static void	display_env(t_mini_shell *ms)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (ms->env && ms->env[i])
	{
		str = ms->env[i];
		j = 0;
		while (str[j] && str[j] != '=')
			j++;
		if (str[j + 1] != '\"' && str[j + 1] != '\'')
			printf("%s\n", ms->env[i]);
		else
			display_env_without_quote(str);
		i++;
	}
}

t_error	ft_env(t_mini_shell *ms)
{
	display_env(ms);
	set_exit_code(EXIT_SUCCESS);
	return (SUCCESS);
}
