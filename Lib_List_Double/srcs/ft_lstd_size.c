/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:20 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:54:58 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

int	ft_lstd_size(t_lstd *lst)
{
	int		i;
	t_lstd	*tmp;

	i = 0;
	tmp = lst;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	if (tmp && tmp->previous)
		i--;
	while (tmp)
	{
		tmp = tmp->previous;
		i++;
	}
	return (i);
}
