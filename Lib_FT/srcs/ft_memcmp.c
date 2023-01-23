/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:40:07 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/09 19:32:18 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	char	*p1;
	char	*p2;
	size_t	i;

	p1 = (char *)pointer1;
	p2 = (char *)pointer2;
	i = 0;
	while (i < size)
	{
		if (p1[i] - p2[i] != 0)
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return (0);
}
