/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:46:43 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/10 14:23:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	count_digits(int n);
static char	*integer_min(void);

char	*ft_itoa(int n)
{
	char	*str;
	int		index;

	if (n == INT_MIN)
		return (integer_min());
	index = count_digits(n) - 1;
	str = malloc(sizeof(char) * (index + 2));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, index + 2);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[index] = n % 10 + '0';
		n /= 10;
		index -= 1;
	}
	return (str);
}

static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		digits += 1;
	}
	while (n > 0)
	{
		n /= 10;
		digits += 1;
	}
	return (digits);
}

static char	*integer_min(void)
{
	char	*str;
	char	*int_min;
	int		i;

	i = 0;
	int_min = "-2147483648";
	str = malloc(sizeof(char) * 12);
	if (str == NULL)
		return (NULL);
	while (int_min[i])
	{
		str[i] = int_min[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
