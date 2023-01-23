/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:41:42 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 15:35:45 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

void	ft_lstd_clear(t_lstd **lst, void (*free_fct)(void *))
{
	t_lstd	*temp;
	t_lstd	*tmp;

	if (!free_fct || !lst)
		return ;
	tmp = *lst;
	while (*lst)
	{
		free_fct((*lst)->content);
		temp = (*lst)->next;
		free((*lst));
		(*lst) = temp;
	}
	while (tmp)
	{
		free_fct(tmp->content);
		temp = tmp->previous;
		free(tmp);
		tmp = temp;
	}
	*lst = NULL;
}
