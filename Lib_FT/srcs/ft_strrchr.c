/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:50 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:56:05 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	c = (char)c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)(&(str[i])));
		i--;
	}
	return (NULL);
}
