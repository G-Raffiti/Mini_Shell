/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:59:59 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/20 13:59:59 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	add_in_classic_env(t_mini_shell *ms, char *key, char *new_value);
t_error	add_in_export_env(t_mini_shell *ms, char *key, char *new_value,
			int which_env);
t_error	change_value_envs(t_env_arg *content, char *new_value);

/**
 * \n Add or replace an argument in dict and his associated char **. \n
 * You DONT have to check before if the key already exist. \n
 * In case of 'which_env=2' and key existing only in one Dict ==>
 * it replace and add the other because its magic
 * @param ms
 * @param key
 * @param new_value
 * @param which_env \n ft_env : 0 \n export_env : 1 \n both : 2
 * @return t_error, as always >>o\<\<
 */
t_error	add_or_replace_in_chosen_env(t_mini_shell *ms, char *key,
										char *new_value, int which_env)
{
	t_lstd			*current;
	t_lstd			*current_sort;

	current = ft_lstd_find(ms->env_dict, key, find_in_dict);
	current_sort = ft_lstd_find(ms->env_sort_dict, key, find_in_dict_sorted);
	if ((current && which_env == 0) || (current && which_env == 2))
	{
		if (replace_in_chosen_env(ms, key, new_value, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (which_env == 2 && !current_sort)
			which_env = 1;
		if (which_env == 0)
			return (SUCCESS);
	}
	if ((current_sort && which_env == 1) || (current_sort && which_env == 2))
	{
		if (replace_in_chosen_env(ms, key, new_value, 1) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (which_env == 2 && !current)
			which_env = 0;
		if (which_env == 1 || (which_env == 2))
			return (SUCCESS);
	}
	return (add_in_chosen_env(ms, key, new_value, which_env));
}

/**
 * \n Replace value by 'new_value in chosen ft_env \n
 * You have to know if the key exist already
 * No both replacement is possible, do it again \>\>o\>\>
 * @param ms
 * @param content\\ dict here
 * @param new_value
 * @param which_env \n ft_env : 0 \n export_env : 1
 * @return t_error
 */
t_error	replace_in_chosen_env(t_mini_shell *ms, char *key, char *new_value,
								int which_env)
{
	t_lstd			*current;
	t_lstd			*current_sort;

	current = ft_lstd_find(ms->env_dict, key, find_in_dict);
	current_sort = ft_lstd_find(ms->env_sort_dict, key, find_in_dict_sorted);
	if (which_env == 0)
	{
		if (change_value_envs(get_env_dict(current->content), \
										new_value) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (fill_env(ms) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else
	{
		if (change_value_envs(get_env_dict(current_sort->content), \
										new_value) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (get_value_env_type(get_env_dict(current_sort->content))
			== MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (fill_export_env(ms) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

/**
 * \n Create and Add an element in the chosen dict.\n
 * Then refresh the correspondant char **.\n
 * Didn't check if the key already exist
 * @param ms
 * @param key
 * @param new_value
 * @param which_env \n 0 : ft_env \n 1 : export_env \n 2 : both \n 3 :
 * for export_env, if 'export ARG' (without '=')
 * @return t_error
 */
t_error	add_in_chosen_env(t_mini_shell *ms, char *key, char *new_value,
							int which_env)
{
	if (which_env == 0)
	{
		if (add_in_classic_env(ms, key, new_value) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	else if (which_env == 1 || which_env == 3)
	{
		if (add_in_export_env(ms, key, new_value, which_env) == MALLOC_ERROR)
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

t_error	add_in_classic_env(t_mini_shell *ms, char *key, char *new_value)
{
	t_env_arg		*dict;
	t_lstd			*element;

	if (new_env_arg(&dict) == MALLOC_ERROR)
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

t_error	add_in_export_env(t_mini_shell *ms, char *key, char *new_value,
							int which_env)
{
	t_env_arg		*dict;
	t_lstd			*element;

	if (new_env_arg(&dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (fill_dict_element(&dict, key, new_value) == MALLOC_ERROR)
		return (free(dict), MALLOC_ERROR);
	if (create_new_list_element(&element, dict) == MALLOC_ERROR)
		return (free(dict->value), free(dict->key), free(dict), MALLOC_ERROR);
	ft_lstd_push_back_elem(&ms->env_sort_dict, element);
	if (get_key_env_type(dict) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (which_env != 3)
	{
		if (get_value_env_type(dict) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		sort_dict(&ms->env_sort_dict, ft_str_cmp);
		if (fill_export_env(ms) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}
