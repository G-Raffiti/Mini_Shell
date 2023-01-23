/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <rbonneva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:46:36 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/22 19:10:58 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*mem;

	if (elementCount != 0 && SIZE_MAX / elementCount < elementSize)
		return (NULL);
	mem = malloc(elementSize * elementCount);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, elementSize * elementCount);
	return (mem);
}
