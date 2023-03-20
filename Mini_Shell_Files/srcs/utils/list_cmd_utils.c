/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:56:35 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:35 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_cmd	*get(t_lstd *lst)
{
	return ((t_cmd *)(lst->content));
}

t_env_arg	*get_env_dict(void *content)
{
	return ((t_env_arg *)(content));
}

void	clear_cmds(t_lstd **lst, void *(*free_fct)(t_cmd *))
{
	t_lstd	*temp;
	t_lstd	*tmp;

	if (!free_fct || !*lst)
		return ;
	tmp = (*lst)->previous;
	while (*lst)
	{
		free_fct(get(*lst));
		temp = (*lst)->next;
		free((*lst));
		(*lst) = temp;
	}
	while (tmp)
	{
		free_fct(get(tmp));
		temp = tmp->previous;
		free(tmp);
		tmp = temp;
	}
	*lst = NULL;
}

void	sort_dict(t_lstd **lst, int (*cmp)())
{
	t_lstd	*a;
	t_lstd	*b;
	void	*tmp;

	if (!lst)
		return ;
	*lst = ft_lstd_first(*lst);
	a = *lst;
	while (a->next)
	{
		b = a->next;
		while (b)
		{
			if (cmp(get_env_dict(a->content)->key,
					get_env_dict(b->content)->key) > 0)
			{
				tmp = a->content;
				a->content = b->content;
				b->content = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}

t_error	create_new_list_element(t_lstd **element, t_env_arg *dict)
{
	*element = ft_lstd_new(dict);
	if (!*element)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
