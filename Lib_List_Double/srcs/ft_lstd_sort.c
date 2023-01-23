/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:24 by rbonneva          #+#    #+#             */
/*   Updated: 2022/12/05 15:01:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lst_sort(t_lstd **lst, int (*cmp)())
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
			if (cmp(a->content, b->content))
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
