/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:51 by rbonneva          #+#    #+#             */
/*   Updated: 2023/02/02 19:49:27 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

///this function retun the first lst that match
///cmp(lst->content, ref) == 1;
///it will search in the next and if not found in the previous elements
t_lstd	*ft_lstd_find(t_lstd *lst, void *ref, int (*cmp)())
{
	t_lstd	*tmp;

	tmp = lst->previous;
	while (lst)
	{
		if (cmp(lst->content, ref))
			return (lst);
		lst = lst->next;
	}
	while (tmp)
	{
		if (cmp(tmp->content, ref))
			return (tmp);
		tmp = tmp->previous;
	}
	return (NULL);
}
