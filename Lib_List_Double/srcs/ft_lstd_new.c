/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_create_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:32:56 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:46:44 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_lstd.h"

t_lstd	*ft_lstd_new(void *content)
{
	t_lstd	*elem;

	if (!content)
		return (NULL);
	elem = malloc(sizeof(t_lstd));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->previous = NULL;
	return (elem);
}
