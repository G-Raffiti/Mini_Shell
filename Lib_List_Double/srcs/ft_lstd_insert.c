/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:53:21 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:36:25 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_insert_elem(t_lstd **lst, t_lstd *elem)
{
	t_lstd	*tmp;

	if (!*lst)
	{
		*lst = elem;
		return ;
	}
	tmp = (*lst)->next;
	(*lst)->next = elem;
	elem->previous = *lst;
	elem->next = tmp;
	if (tmp)
		tmp->previous = elem;
	*lst = elem;
}

t_error	ft_lstd_insert(t_lstd **lst, void *content)
{
	t_lstd	*elem;

	elem = ft_lstd_new(content);
	if (!elem)
		return (MALLOC_ERROR);
	ft_lstd_insert_elem(lst, elem);
	return (SUCCESS);
}
