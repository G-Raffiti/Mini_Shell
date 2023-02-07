//
// Created by aurel on 2/6/23.
//

#include "../../incs/mini_shell.h"


t_error	change_value_envs(t_env_arg *content, char *new_value, int which_env)
{
	content->value = ft_free(content->value);
	if (which_env == 1)
	{
		content->value = ft_strjoin("=", new_value);
		if (!content->value)
			return (MALLOC_ERROR);
	}
	else
	{
		content->value = ft_strdup(new_value);
		if (!content->value)
			return (MALLOC_ERROR);
	}
	if (!content->value)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

/**
 * Replace value by 'new_value in dict/ env, you have to set right content (get_env_dict(current->content)).
 * @param ms
 * @param content
 * @param new_value
 * @param which_env
 * @return t_error
 */
t_error	replace_in_chosen_env(t_mini_shell *ms, t_env_arg *content, char *new_value, int which_env)
{
	change_value_envs(content, new_value, which_env);
	if (which_env == 0)
	{
		if (fill_env(ms) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else
	{
		if (fill_export_env(ms) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (get_value_env_type(content) == MALLOC_ERROR)
			return (MALLOC_ERROR);
//		get_export_type(ms);
	}
	return (SUCCESS);
}

t_error	create_new_list_element(t_lstd **element, t_env_arg *dict)
{
	*element = ft_lstd_new(dict);
	if (!*element)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	fill_dict_element(t_env_arg **dict, char *key, char *value)
{

	(*dict)->value = ft_strdup(value);
	if (!(*dict)->value)
		return (MALLOC_ERROR);
	(*dict)->key = ft_strdup(key);
	if (!(*dict)->key)
		return (free((*dict)->value), MALLOC_ERROR);
	return (SUCCESS);
}

t_error	add_in_classic_env(t_mini_shell *ms, char *key, char *new_value)
{
	t_env_arg		*dict;
	t_lstd			*element;

	if (create_new_dict_element(&dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (fill_dict_element(&dict, key, new_value) == MALLOC_ERROR)
		return (free(dict), MALLOC_ERROR);
	if (create_new_list_element(&element, dict) == MALLOC_ERROR)
		return (free(dict->value), free(dict->key), free(dict), MALLOC_ERROR);
	ft_lstd_push_back_elem(&ms->env_dict, element);
	if (fill_env(ms) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	add_in_export_env(t_mini_shell *ms, char *key, char *new_value)
{
	t_env_arg		*dict;
	t_lstd			*element;

	if (create_new_dict_element(&dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (fill_dict_element(&dict, key, new_value) == MALLOC_ERROR)
		return (free(dict), MALLOC_ERROR);
	if (create_new_list_element(&element, dict) == MALLOC_ERROR)
		return (free(dict->value), free(dict->key), free(dict), MALLOC_ERROR);
	ft_lstd_push_back_elem(&ms->env_sort_dict, element);
	if (get_key_env_type(dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (get_value_env_type(dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	sort_dict(&ms->env_sort_dict, ft_str_cmp);
	if (fill_export_env(ms) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (MALLOC_ERROR);
}

t_error	add_or_replace_in_chosen_env(t_mini_shell *ms, char *key, char *new_value, int which_env)
{
	t_lstd			*current;
	t_lstd			*current_export;

	current = ft_lstd_find(ms->env_dict, key, find_in_dict);
	current_export = ft_lstd_find(ms->env_sort_dict, key, find_in_dict_sorted);
	if ((current && which_env == 0) || (current && which_env == 2))
	{
		if (replace_in_chosen_env(ms, get_env_dict(current), new_value, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (which_env == 0)
			return (SUCCESS);
	}
	if ((current_export && which_env == 1) || (current_export && which_env == 2))
	{
		if (replace_in_chosen_env(ms, get_env_dict(current_export), new_value, 1) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (which_env == 1 || (which_env == 2 && current))
			return (SUCCESS);
	}
	return (add_in_chosen_env(ms, key, new_value, which_env), ERROR);
}
/**
 * Create and Add an element in the chosen dict (which env), then refresh the correspondant char **.\n
 * If Key already exist , do nothing.
 * @param ms
 * @param key
 * @param new_value
 * @param which_env \n 0 : env \n 1 : export_env \n 2 : both
 * @return t_error
 */
t_error	add_in_chosen_env(t_mini_shell *ms, char *key, char *new_value, int which_env)
{
	if (which_env == 0)
	{
		if (add_in_classic_env(ms, key, new_value) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else if (which_env == 1)
	{
		if (add_in_export_env(ms, key, new_value) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else if (which_env == 2)
	{
		if (add_in_chosen_env(ms, key, new_value, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (add_in_chosen_env(ms, key, new_value, 1) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}
