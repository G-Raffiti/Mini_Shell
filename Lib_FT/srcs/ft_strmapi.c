/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:47:08 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/24 17:14:51 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	str = ft_strdup((char *)s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
