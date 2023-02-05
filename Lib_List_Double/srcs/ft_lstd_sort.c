/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:24 by rbonneva          #+#    #+#             */
/*   Updated: 2023/02/05 16:51:04 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_sort(t_lstd **lst, int (*cmp)())
{
	t_lstd	*a;
	t_lstd	*b;
	void	*tmp;

	if (!lst)
		return ;
	*lst = ft_lstd_first(*lst);
	a = *lst;
	while (a->next)
	{
		b = a->next;
		while (b)
		{
			if (cmp(a->content, b->content) < 0)
			{
				tmp = a->content;
				a->content = b->content;
				b->content = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}
