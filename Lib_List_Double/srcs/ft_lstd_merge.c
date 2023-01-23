/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:33 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 16:04:15 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

///WARNING by using this function you will lose track of the previous element
// in begin2
void	ft_lstd_merge(t_lstd **begin1, t_lstd *begin2)
{
	t_lstd	*last;

	if (!begin1)
		return ;
	if (*begin1)
	{
		last = ft_lstd_last(*begin1);
		last->next = begin2;
		begin2->previous = last;
	}
	else
		*begin1 = begin2;
}
