/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:04 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:36:25 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lst_push_front(t_lstd **lst, void *data)
{
	t_lstd	*elem;

	if (*lst)
	{
		elem = ft_lstd_new(data);
		if (!elem)
			return ;
		elem->next = ft_lstd_first(*lst);
		elem->next->previous = elem;
		*lst = elem;
	}
	else
		*lst = ft_lstd_new(data);
}

///WARNING by using thin function you will lose the next and previous
/// elements of elem
void	ft_lst_push_front_elem(t_lstd **begin, t_lstd *elem)
{
	if (elem)
	{
		elem->next = NULL;
		elem->previous = NULL;
	}
	if (!(*begin))
		*begin = elem;
	else
	{
		elem->next = *begin;
		(*begin)->previous = elem;
		*begin = elem;
	}
}
