/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:01 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:36:25 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_push_back(t_lstd **lst, void *data)
{
	t_lstd	*last;

	if (*lst)
	{
		last = ft_lstd_last(*lst);
		last->next = ft_lstd_new(data);
		last->next->previous = last;
	}
	else
		*lst = ft_lstd_new(data);
}

/// WARNING by using this function you will loose the next and previous
/// elements in elem's list
void	ft_lst_push_back_elem(t_lstd **lst, t_lstd *elem)
{
	t_lstd	*last;

	if (elem)
	{
		elem->next = NULL;
		elem->previous = NULL;
	}
	if (*lst)
	{
		last = ft_lstd_last(*lst);
		elem->next->previous = NULL;
		last->next = elem;
		elem->previous = last;
	}
	else
		*lst = elem;
}
