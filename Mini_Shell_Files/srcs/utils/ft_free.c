/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:42 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:42 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../incs/mini_shell.h"

void	*ft_free(void *pt)
{
	if (pt)
		free(pt);
	return (NULL);
}

void	*free_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
		split[i] = ft_free(split[i]);
	split = ft_free(split);
	return (NULL);
}
