/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:58 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 15:35:45 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lst_for_if(t_lstd *lst, void (*f)(void *), void *ref, int (*cmp)())
{
	t_lstd	*tmp;

	if (!f || !cmp)
		return ;
	tmp = lst;
	while (lst)
	{
		if (cmp(lst->content, ref))
			f(lst->content);
		lst = lst->next;
	}
	while (tmp)
	{
		if (cmp(tmp->content, ref))
			f(tmp->content);
		tmp = tmp->previous;
	}
}
