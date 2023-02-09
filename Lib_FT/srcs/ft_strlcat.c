/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:36:57 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:47:49 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	while (src[i])
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = 0;
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (size != 0)
		len = ft_strlen(dest);
	else
		return (ft_strlen(src));
	if (len >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && i + len < size - 1)
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = 0;
	len += ft_strlen(src);
	return (len);
}
