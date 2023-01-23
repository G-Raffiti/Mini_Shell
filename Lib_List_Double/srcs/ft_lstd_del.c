/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:13 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 16:22:04 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_del(t_lstd *elem, void (*free_fct)(void *))
{
	if (elem)
	{
		elem->next->previous = elem->previous;
		elem->previous->next = elem->next;
		free_fct(elem->content);
		free(elem);
	}
}
