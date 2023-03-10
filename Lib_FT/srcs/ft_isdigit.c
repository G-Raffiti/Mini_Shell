/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:31:03 by rbonneva          #+#    #+#             */
/*   Updated: 2022/12/19 22:24:18 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	ft_is_digit_signed(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') && *str != '-' && *str != '+')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
