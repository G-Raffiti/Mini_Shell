#include "../../incs/mini_shell.h"

t_error	fill_dict_element(t_env_arg **dict, char *key, char *value)
{
	(*dict)->value = ft_strdup(value);
	if (!(*dict)->value)
		return (MALLOC_ERROR);
	(*dict)->key = ft_strdup(key);
	if (!(*dict)->key)
	{
		(*dict)->value = ft_free((*dict)->value);
		return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

t_error	change_value_envs(t_env_arg *content, char *new_value)
{
	content->value = ft_free(content->value);
	content->value = ft_strdup(new_value);
	if (!content->value)
		return (MALLOC_ERROR);
	if (!content->value)
		return (MALLOC_ERROR);
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
int	find_in_dict_sorted(void *content, void *ref)
{
	if (ft_str_cmp(get_env_dict(content)->key, "_") == 0)
		return (0);
	if (ft_str_cmp((get_env_dict(content)->key + 11), (char *)ref) == 0)
		return (1);
	return (0);
}
