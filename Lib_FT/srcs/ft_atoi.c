/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:41:00 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/24 16:56:59 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	atoi_overflow(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	last;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_contain(" \t\v\r\n\f", *str))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_contain("0123456789", *str))
	{
		last = i;
		i *= 10;
		if (last != i / 10)
			return (atoi_overflow(sign));
		i += *str - '0';
		str++;
	}
	return ((int)(i * sign));
}
