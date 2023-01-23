/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:28 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:55:17 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)(&(str[i])));
		i++;
	}
	if (c == 0)
		return ((char *)(&(str[i])));
	return (NULL);
}
