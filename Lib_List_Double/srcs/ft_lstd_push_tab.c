/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_strs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:42:07 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:42:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

t_lstd	*ft_lstd_push_tab(int size, void **data)
{
	t_lstd	*lst;

	lst = NULL;
	while (--size >= 0)
		ft_lstd_push_front(&lst, data[size]);
	return (lst);
}
