/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:02:32 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/19 01:39:58 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"
#include <stdarg.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		len1;

	if (s1 == NULL)
		return (ft_strdup((char *)s2));
	len1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[len1 + i] = s2[i];
		i++;
	}
	str[len1 + i] = 0;
	return (str);
}

char	*ft_strjoins(int argc, ...)
{
	va_list	ap;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	va_start(ap, argc);
	while (argc > 0)
	{
		tmp = ft_strjoin(str, va_arg(ap, char *));
		if (str)
			free(str);
		str = tmp;
		argc--;
	}
	va_end(ap);
	return (str);
}
