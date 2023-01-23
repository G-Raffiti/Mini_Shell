/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:36:29 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:21:04 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size <= 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i += 1;
	}
	if (size > ft_strlen(src))
		dest[i] = 0;
	else
		dest[size - 1] = 0;
	return (ft_strlen(src));
}
