
#include "../../incs/mini_shell.h"


t_error	get_key_env_type(t_env_arg *content)
{
	char 	*tmp;

	if (ft_str_cmp(content->key, "_") != 0)
	{
		tmp = ft_strdup(content->key);
		if (!tmp)
			return (MALLOC_ERROR);
		content->key = ft_free(content->key);
		content->key = ft_strjoin("declare -x ", tmp);
		if (!content->key)
			return (MALLOC_ERROR);
		tmp = ft_free(tmp);
	}
	return (SUCCESS);
}

t_error	get_value_env_type(t_env_arg *content)
{
	char 	*tmp;

	tmp = ft_strdup(content->value);
	if (!tmp)
		return (MALLOC_ERROR);
	content->value = ft_free(content->value);
	content->value = ft_strjoin("=\"", tmp);
	if (!content->value)
		return (MALLOC_ERROR);
	tmp = ft_free(tmp);
	tmp = ft_strdup(content->value);
	if (!tmp)
		return (MALLOC_ERROR);
	content->value = ft_free(content->value);
	content->value = ft_strjoin(tmp, "\"");
	if (!content->value)
		return (MALLOC_ERROR);
	tmp = ft_free(tmp);
	return (SUCCESS);
}

t_error	get_export_type(t_mini_shell *ms)
{
	t_lstd		*current;
	t_env_arg	*content;

	current = ms->env_sort_dict;
	while (current)
	{
		content = get_env_dict(current->content);
		{
			if (get_key_env_type(content) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			if (get_value_env_type(content) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}

/**
 * Find in dict ENV
 * @param content
 * @param ref
 * @return 1 if find else 0
 */
int	find_in_dict(void *content, void *ref)
{
	if (ft_str_cmp(get_env_dict(content)->key, (char *)ref) == 0)
		return (1);
	return (0);
}

/**
 * Find in dict EXPORT
 * @param content
 * @param ref
 * @return if find : 1 \n else : 0
 */
int find_in_dict_sorted(void *content, void *ref)
{
	if (ft_str_cmp((get_env_dict(content)->key + 11), (char *)ref) == 0)
		return (1);
	return (0);
}

t_error get_keys(t_env_arg **env_dict, char *env)
{
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
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
	while (dup_line[i] && dup_line[i] != '=')
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

t_error	create_export_env(t_mini_shell *ms)
{
	t_env_arg *env_sort_dict;
	t_lstd *current_sort;
	int key_index;

	key_index = -1;
	while (++key_index < ft_strlen_tab(ms->env))
	{
		if (create_new_dict_element(&env_sort_dict) == MALLOC_ERROR)
			exit_malloc(ms, "env: create_new_dict_element");
		if (get_keys(&env_sort_dict, ms->env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_keys");
		if (get_values(&env_sort_dict, ms->env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_values");
		current_sort = ft_lstd_new(env_sort_dict);
		if (!current_sort)
			exit_malloc(ms, "env: new_lstd");
		ft_lstd_push_back_elem(&ms->env_sort_dict, current_sort);
	}
	return (SUCCESS);
}

t_error	get_env(t_mini_shell *ms, char **env)
{
	t_env_arg *env_dict;
	t_lstd *current;
	int key_index;

	key_index = -1;
	if (dup_env(ms, env) == MALLOC_ERROR)
		exit_malloc(ms, "env: dup_env");
	while (++key_index < ft_strlen_tab(env))
	{
		if (create_new_dict_element(&env_dict) == MALLOC_ERROR)
			exit_malloc(ms, "env: create_new_dict_element");
		if (get_keys(&env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_keys");
		if (get_values(&env_dict, env[key_index]) == MALLOC_ERROR)
			exit_malloc(ms, "env: get_values");
		current = ft_lstd_new(env_dict);
		if (!current)
			exit_malloc(ms, "env: new_lstd");
		ft_lstd_push_back_elem(&ms->env_dict, current);
	}
	return (SUCCESS);
}

t_error fill_new_envs(t_lstd *current, char **str, int which_env)
{
	t_lstd		*content;
	char		*value;
	char 		*key;

	content = current->content;
	if ((which_env == 0 || which_env == 2))
		value = ft_strjoin("=", get_env_dict(content)->value);
	else
		value = get_env_dict(content)->value;
	key = get_env_dict(content)->key;
	*str = ft_strjoin(key, value);
	if (!*str)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	refresh_env(t_mini_shell *ms)
{
	int			size_dict;

	ms->env = ft_free(ms->env);
	size_dict = ft_lstd_size(ms->env_dict);
	ms->env = ft_calloc(size_dict, sizeof(char *));
	if (!ms->env_sort)
		return (MALLOC_ERROR);
	ms->env[size_dict - 1] = NULL;
	return (SUCCESS);
}

t_error	refresh_export_env(t_mini_shell *ms)
{
	int			size_sorted_dict;

	ms->env_sort = ft_free(ms->env_sort);
	if (ms->exported)
		size_sorted_dict = ft_lstd_size(ms->env_sort_dict);
	else
		size_sorted_dict = ft_lstd_size(ms->env_dict);
	ms->env_sort = ft_calloc(size_sorted_dict, sizeof(char *));
	if (!ms->env_sort)
		return (MALLOC_ERROR);
	ms->env_sort[size_sorted_dict - 1] = NULL;
	return (SUCCESS);
}

t_error	fill_export_env(t_mini_shell *ms)
{
	t_lstd		*current;
	int 		i;

	i = 0;
	refresh_export_env(ms);
	current = ms->env_sort_dict;
	while (current)
	{
		if (ft_str_cmp(get_env_dict(current->content)->key, "_") != 0)
		{
			if (fill_new_envs(current, &(ms->env_sort)[i], 1) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			i++;
		}
		current = current->next;
	}
	i = 0;
//	while (ms->env_sort[i])
//	{
//		dprintf(2, "%s\n", ms->env_sort[i]);
//		i++;
//	}
	ms->exported = TRUE;
	return (SUCCESS);
}

t_error	fill_env(t_mini_shell *ms)
{
	t_lstd		*current;
	int 		i;

	i = 0;
	refresh_env(ms);
	current = ms->env_dict;
	while (current)
	{
		if (fill_new_envs(current, &(ms->env)[i], 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		i++;
		current = current->next;
	}
//	i = 0;
//	while (ms->env_sort[i])
//	{
//		dprintf(2, "%s\n", ms->env_sort[i]);
//		i++;
//	}
	return (SUCCESS);
}
// TODO [Aurel]: synchro list env to char** env
// TODO [Aurel]: synchro char** env to list env