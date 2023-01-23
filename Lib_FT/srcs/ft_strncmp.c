/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:47:11 by rbonneva          #+#    #+#             */
/*   Updated: 2022/12/19 22:44:02 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length && (first[i] || second[i]))
	{
		if (first[i] - second[i] != 0)
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return (0);
}

int	ft_str_cmp(const char *first, const char *second)
{
	size_t	i;

	i = 0;
	while (first[i] || second[i])
	{
		if (first[i] - second[i] != 0)
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return (0);
}
