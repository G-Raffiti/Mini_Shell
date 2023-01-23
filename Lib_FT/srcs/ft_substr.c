/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:52:19 by marvin            #+#    #+#             */
/*   Updated: 2022/11/07 21:52:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (s == NULL)
		return (NULL);
	if (start < ft_strlen(s))
		while (s[start + size] && size < len)
			size++;
	else
		size = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	str[size] = 0;
	return (str);
}
