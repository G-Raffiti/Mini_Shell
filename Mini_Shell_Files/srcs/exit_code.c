/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:55:38 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:55:38 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_exit_code;

void	set_exit_code(int value)
{
	g_exit_code = value;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}
