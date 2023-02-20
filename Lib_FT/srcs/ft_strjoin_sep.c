/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:18:23 by aucaland          #+#    #+#             */
/*   Updated: 2022/09/20 18:18:49 by aucaland         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strjoin_split(char **split, char sep)
{
	size_t	len;
	int		i;
	char	*str;

	len = 0;
	i = -1;
	while (split[++i])
		len += ft_strlen(split[i]) + 1;
	if (!len)
		len = 1;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	len = 0;
	while (split[++i])
	{
		ft_strcat(str, split[i]);
		len += ft_strlen(split[i]);
		if (split[i + 1])
			str[len] = sep;
	}
	return (str);
}

int	final_size(char **strs, char *sep, int size)
{
	int	i;
	int	j;
	int	final_size;
	int	len_sep;

	final_size = 0;
	i = 0;
	j = 0;
	len_sep = 0;
	while (sep[len_sep])
		len_sep++;
	while (i < size)
	{
		while (strs[i][j])
		{
			final_size++;
			j++;
		}
		i++;
		j = 0;
	}
	final_size = final_size + (size * len_sep) - len_sep;
	return (final_size);
}

char	*ft_concaten(char *strs_final, char **strs, char *sep, int size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < size)
	{
		while (strs[i][k])
			strs_final[j++] = strs[i][k++];
		k = 0;
		if (i < size - 1)
		{
			while (sep[k])
				strs_final[j++] = sep[k++];
		}
		k = 0;
		i++;
	}
	strs_final[j] = '\0';
	return (strs_final);
}

char	*ft_strjoin_sep(int size, char **strs, char *sep)
{
	char	*strs_final;

	if (size == 0)
	{
		strs_final = malloc(sizeof(char) * 1);
		if (!strs_final)
			return (0);
		return (strs_final);
	}
	strs_final = malloc(sizeof(char) * (final_size(strs, sep, size) + 1));
	if (!strs_final)
		return (0);
	return (ft_concaten(strs_final, strs, sep, size));
}
