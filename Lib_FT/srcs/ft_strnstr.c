/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:40:32 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 18:24:49 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!big || len == 0)
		return (NULL);
	if (little_len == 0)
		return ((char *)big);
	while (big[i] && i + little_len <= len)
	{
		if (big[i] == little[0])
		{
			if (!ft_strncmp(&(big[i]), little, little_len))
				return ((char *)(&(big[i])));
		}
		i++;
	}
	return (NULL);
}
