
#include "../../incs/mini_shell.h"

/// cmp func to not use exept in get_env_value
int find_in_dict(void *content, void *ref)
{
	if (ft_str_cmp(get_env_dict(content)->key, (char *)ref) == 0)
		return (1);
	return (0);
}

t_error get_keys(t_env_arg **env_dict, char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	(*env_dict)->key = ft_substr(env, 0, i);
	if (!(*env_dict)->key)
		return (free(*env_dict), MALLOC_ERROR);
	return (SUCCESS);
}

t_error get_values(t_env_arg **env_dict, char *env)
{
	int		i;
	int		len_line;
	char	*dup_line;

	i = 0;
	len_line = ft_strlen(env);
	dup_line = ft_strdup(env);
	if (!dup_line)
		return (MALLOC_ERROR);
	while (dup_line[i] != '=')
		i++;
	(*env_dict)->value = ft_substr(dup_line, i + 1, len_line);
	free(dup_line);
	if (!(*env_dict)->value)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	dup_env(t_mini_shell *ms, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (ERROR);//TODO : check redir
	ms->env = ft_calloc(sizeof(char *), ft_strlen_tab(env) + 1);
	if (!ms->env)
		return(MALLOC_ERROR);
	while (env[i])
	{
		ms->env[i] = ft_strdup(env[i]);
		if(!ms->env[i])
			return(free_split(ms->env), MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}

void	get_env(t_mini_shell *ms, char **env)
{
	t_env_arg	*env_dict;
	t_lstd		*current;
	int 		key_index;

	key_index = -1;
	if (dup_env(ms, env) == MALLOC_ERROR)
		exit_malloc(ms, "env: dup_env");
	while (++key_index < ft_strlen_tab(env))
	{
		if (new_env_args(&env_dict) == MALLOC_ERROR)
			exit_malloc(ms, "env: new_env_args");
		if (get_keys(&env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_keys");
		if (get_values(&env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_values");
		current = ft_lstd_new(env_dict);
		if (!current)
			return (free_split(ms->env), \
						ft_lstd_clear(&ms->env_dict, ft_free));
		ft_lstd_push_back_elem(&ms->env_dict, current);
	}
}

// TODO [Aurel]: synchro list env to char** env
// TODO [Aurel]: synchro char** env to list env