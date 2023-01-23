/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:13 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:09:01 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_remove_if(t_lstd **lst, void *ref, \
						int (*cmp)(), void (*free_fct)(void *))
{
	t_lstd	*current;
	t_lstd	*tmp;

	current = ft_lstd_first(*lst);
	while (current)
	{
		tmp = current->next;
		if (cmp(current->content, ref))
		{
			ft_lstd_del(current, free_fct);
		}
		else
			*lst = current;
		current = tmp;
	}
	*lst = ft_lstd_first(*lst);
}
