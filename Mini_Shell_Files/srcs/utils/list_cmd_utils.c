
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
			if (cmp(get_env_dict(a->content)->key, get_env_dict(b->content)->key) > 0)
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
