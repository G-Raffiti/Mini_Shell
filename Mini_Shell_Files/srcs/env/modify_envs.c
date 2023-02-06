//
// Created by aurel on 2/6/23.
//

#include "../../incs/mini_shell.h"


t_error	change_value_envs(t_env_arg *content, char *new_value)
{
	content->value = ft_free(content->value);
	content->value = ft_strjoin("=", new_value);
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
	change_value_envs(content, new_value);
	if (which_env == 0)
		fill_env(ms);
	else
	{
		fill_export_env(ms);
		get_value_env_type(content);
	}
	return (SUCCESS);
}

t_error	create_new_list_element(t_lstd **element, t_env_arg *dict, char *value, char *key)
{
	*element = ft_lstd_new(dict);
	if (!*element)
		return (MALLOC_ERROR);
}

/**
 * Create and Add an element in the chosen dict (which_env = 0 for env or 1 for export), then refresh the correspondant char **.
 * @param ms
 * @param key
 * @param value
 * @param which_env
 * @return t_error
 */
t_error	add_in_chosen_env(t_mini_shell *ms, char *key, char *value, int which_env)
{
	t_env_arg	*dict;
	t_lstd		*element

	if (ft_str_cmp(value, "_") != 0)
		return (ERROR);//TODO : check return
	if (which_env == 0)
	{
		if (create_new_dict_element(&dict) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (create_new_list_element(&element, dict, value, key) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		ft_lstd_push_back_elem(&ms->env_dict, element);
	}
}
