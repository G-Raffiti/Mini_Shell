
#include "../incs/mini_shell.h"

t_cmd	*get(t_lstd *lst)
{
	return ((t_cmd *)(lst->content));
}

t_arg_env	*get_arg_env(void *content)
{
	return ((t_arg_env *)(content));
}