/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    ft_lst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:29 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:42:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

t_lstd	*ft_lstd_first(t_lstd *lst)
{
	while (lst && lst->previous)
		lst = lst->previous;
	return (lst);
}
