/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:10:56 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/24 17:20:12 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	count_word(char *s, char c);
static void	free_split(char **split, int words);
static void	fill_split(char **split, char *s, char c);

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	if (s == NULL)
		return (NULL);
	words = count_word((char *)s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	split[words] = 0;
	fill_split(split, (char *)s, c);
	return (split);
}

static int	count_word(char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			while (*s && *s != c)
				s++;
			words++;
		}
	}
	return (words);
}

static void	free_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i <= words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	fill_split(char **split, char *s, char c)
{
	int	letters;
	int	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			letters = 0;
			while (s[letters] != c && s[letters])
				letters++;
			split[words] = ft_substr(s, 0, letters);
			if (split[words] == NULL)
			{
				free_split(split, words);
				return ;
			}
			s += letters;
			words++;
		}
	}
}
