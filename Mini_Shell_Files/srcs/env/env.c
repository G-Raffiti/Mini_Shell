
#include "../../incs/mini_shell.h"

t_error get_keys(t_env_arg *env_dict, char *env)
{
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	env_dict->key = ft_substr(env, 0, i);
	if (!env_dict->key)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error get_values(t_env_arg *env_dict, char *env_line)
{
	while (*env_line && *env_line != '=')
		env_line++;
	env_line++;
	env_dict->value = ft_substr(env_line, 0, ft_strlen(env_line));
	if (!env_dict->value)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	dup_env(t_mini_shell *ms, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (ERROR);//TODO : REGEN_ENV
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

t_error	get_export_env(t_mini_shell *ms)
{
	t_env_arg *env_sort_dict;
	t_lstd *current_sort;
	int key_index;

	key_index = -1;
	while (++key_index < ft_strlen_tab(ms->env))
	{
		if (new_env_arg(&env_sort_dict) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: new_env_arg");
		if (get_keys(env_sort_dict, ms->env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: get_keys");
		if (get_values(env_sort_dict, ms->env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: get_values");
		if (create_new_list_element(&current_sort, env_sort_dict) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: new_lstd");
		ft_lstd_push_back_elem(&ms->env_sort_dict, current_sort);
	}
	if (get_export_type(ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: get_export_type");
	sort_dict(&ms->env_sort_dict, ft_str_cmp);
	if (fill_export_env(ms) == MALLOC_ERROR)
		exit_malloc(ms, "main: sort_export_and_fill_export_env");
	return (SUCCESS);
}

t_error	get_env(t_mini_shell *ms, char **env)
{
	t_env_arg	*env_dict;
	t_lstd		*current;
	int			key_index;

	key_index = -1;
	if (dup_env(ms, env) == MALLOC_ERROR)
		exit_malloc(ms, "ft_env: dup_env");
	while (++key_index < ft_strlen_tab(env))
	{
		if (new_env_arg(&env_dict) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: new_env_arg");
		if (get_keys(env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: get_keys");
		if (get_values(env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: get_values");
		if (create_new_list_element(&current, env_dict) == MALLOC_ERROR)
			exit_malloc(ms, "ft_env: new_lstd");
		ft_lstd_push_back_elem(&ms->env_dict, current);
	}
	return (SUCCESS);
}
