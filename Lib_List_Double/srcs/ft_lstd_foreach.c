/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:54 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 15:35:46 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_foreach(t_lstd *lst, void (*f)(void *))
{
	t_lstd	*tmp;

	if (!f)
		return ;
	tmp = lst;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->previous;
	}
}
