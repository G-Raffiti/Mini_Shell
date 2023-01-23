/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:37:13 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/08 13:37:13 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	len;
	int	start;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup((char *)s1));
	len = ft_strlen(s1) - 1;
	start = 0;
	while (ft_contain((char *)set, s1[len]))
		len--;
	while (ft_contain((char *)set, s1[start]))
	{
		start++;
		len--;
	}
	return (ft_substr(s1, start, len + 1));
}
