
#include "../../incs/mini_shell.h"

t_error	new_env_args(t_env_arg **env_dict)
{
	*env_dict = malloc(sizeof(t_env_arg));
	if (!*env_dict)
		return (MALLOC_ERROR);
	(*env_dict)->key = NULL;
	(*env_dict)->value = NULL;
	return (SUCCESS);
}

t_error get_keys(t_env_arg **env_dict)
{
	int		i;

	i = 0;
	while ((*env_dict)->value[i] != '=')
		i++;
	(*env_dict)->key = ft_substr((*env_dict)->value, 0, i);
	if (!(*env_dict)->key)
		return (free(*env_dict), MALLOC_ERROR);
	return (SUCCESS);
}

t_error	dup_env(t_mini_shell *ms, char **env)
{
	int	i;

	i = 0;
	ms->env = ft_calloc(sizeof(char *), ft_strlen_tab(env) + 1);
	if (!ms->env)
		return(ms->env = free_split(ms->env), MALLOC_ERROR);
	while (env[i])
	{
		ms->env[i] = ft_strdup(env[i]);
		if(!ms->env[i])
			return(free_split(ms->env), MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}

void	get_env(t_mini_shell *mini_shell, char **env)
{
	t_env_arg	*env_dict;
	t_lstd		*current;
	int 		key_index;

	key_index = -1;
	if (dup_env(mini_shell, env) == MALLOC_ERROR)
		exit_malloc(mini_shell);
	while (++key_index < ft_strlen_tab(env))
	{
		if (new_env_args(&env_dict) == MALLOC_ERROR)
			exit_malloc(mini_shell);
		env_dict->value =  mini_shell->env[key_index];
		if (get_keys(&env_dict) == MALLOC_ERROR)
			exit_malloc(mini_shell);
		current = ft_lstd_new(env_dict);
		if (!current)
			return (free_split(mini_shell->env), \
						ft_lstd_clear(&mini_shell->env_dict, (void*)free));
		ft_lstd_push_back_elem(&mini_shell->env_dict, current);
	}
	// TODO [Aurel]: create list of env_args (char* key / char** value)
	// ATTENTION garder les / a la fin des PATH
}

void	set_env(t_mini_shell *ms, char **env)
{
	(void)ms;
	(void)env;
}
// TODO [Aurel]: synchro list env to char** env
// TODO [Aurel]: synchro char** env to list env