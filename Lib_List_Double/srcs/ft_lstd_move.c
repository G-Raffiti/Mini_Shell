/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:10:50 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 17:28:19 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_move(t_lstd **from, t_lstd *elem, t_lstd *after_this)
{
	*from = ft_lstd_remove(elem);
	ft_lstd_insert_elem(&after_this, elem);
}
