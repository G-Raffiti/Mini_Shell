/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:10:50 by rbonneva          #+#    #+#             */
/*   Updated: 2023/02/09 22:56:33 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

/// returns the next elem in list
t_lstd	*ft_lstd_remove(t_lstd *elem)
{
	t_lstd	*lst;

	if (!elem)
		return (NULL);
	if (elem->next)
		lst = elem->next;
	else if (elem->previous)
		lst = elem->previous;
	else
		lst = NULL;
	if (elem->previous)
		elem->previous->next = elem->next;
	if (elem->next)
		elem->next->previous = elem->previous;
	elem->next = NULL;
	elem->previous = NULL;
	return (lst);
}

t_lstd	*ft_lstd_remove_and_del(t_lstd *elem, void (*free_fct)(void *))
{
	t_lstd	*lst;

	lst = ft_lstd_remove(elem);
	ft_lstd_del(elem, free_fct);
	return (lst);
}
