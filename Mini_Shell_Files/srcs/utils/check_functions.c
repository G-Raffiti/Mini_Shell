/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:17 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:57:17 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

int	valid_id_dollars(char c)
{
	if (ft_contain(INV_ID, c) || c >= 127 || c == ' ')
		return (0);
	return (1);
}

int	valid_id_export(char c)
{
	if (ft_contain(INV_ID_EXPORT, c) || c >= 127 || c == ' ')
		return (0);
	return (1);
}

int	is_not_alpha(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}
