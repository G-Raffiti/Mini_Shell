
#include "../incs/mini_shell.h"

void	clear_cmds(t_lstd **cmds)
{
	ft_lstd_clear(cmds, (void (*)(void *))free_cmd);
}

t_cmd	*get(t_lstd *lst)
{
	return ((t_cmd *)(lst->content));
}

t_env_arg	*get_env_dict(void *content)
{
	return ((t_env_arg *)(content));
}