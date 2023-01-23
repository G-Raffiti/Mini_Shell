/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:17 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:42:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_reverse(t_lstd **lst)
{
	t_lstd	*tmp;

	*lst = ft_lstd_first(*lst);
	while (*lst)
	{
		tmp = (*lst)->previous;
		(*lst)->previous = (*lst)->next;
		(*lst)->next = tmp;
		*lst = (*lst)->previous;
	}
}
