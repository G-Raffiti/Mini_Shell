/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:37 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:42:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

t_lstd	*ft_lstd_at(t_lstd *lst, unsigned int nbr)
{
	lst = ft_lstd_first(lst);
	while (lst && nbr-- > 0)
		lst = lst->next;
	return (lst);
}
