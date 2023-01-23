/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_contain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:31:25 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 20:01:39 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

int	ft_lstd_contain(t_lstd *lst, void *content)
{
	t_lstd	*tmp;

	tmp = lst;
	while (lst)
	{
		if (lst->content == content)
			return (1);
		lst = lst->next;
	}
	while (tmp)
	{
		if (tmp->content == content)
			return (1);
		tmp = tmp->previous;
	}
	return (0);
}
