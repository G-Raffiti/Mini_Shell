/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:10:50 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:10:50 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

t_lstd	*ft_lstd_remove(t_lstd *elem)
{
	t_lstd	*lst;

	lst = NULL;
	if (!elem)
		return (NULL);
	if (elem->previous)
		lst = elem->previous;
	else if (elem->next)
		lst = elem->next;
	if (elem->previous)
		elem->previous->next = elem->next;
	if (elem->next)
		elem->next->previous = elem->previous;
	elem->next = NULL;
	elem->previous = NULL;
	return (lst);
}
