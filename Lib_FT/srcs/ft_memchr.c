/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:39:42 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:56:39 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	c = (char)c;
	p = (char *)s;
	while (i < n)
	{
		if (p[i] == c)
			return ((void *)(&(s[i])));
		i++;
	}
	return (NULL);
}
