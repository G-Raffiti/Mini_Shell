/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:51 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 15:35:46 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

///this function retun the first lst that match
///cmp(lst->content, ref) == 1;
///it will search in the next and if not found in the previous elements
t_lstd	*ft_lstd_find(t_lstd *lst, void *ref, int (*cmp)())
{
	t_lstd	*tmp;

	tmp = lst;
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
