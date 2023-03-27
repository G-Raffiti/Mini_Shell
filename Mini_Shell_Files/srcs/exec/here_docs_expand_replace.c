/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_expand_replace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:30:37 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 18:32:40 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mini_shell.h"

t_error	get_key_and_replace_doc(char **raw, t_env_arg **key_value, char *key)
{
	if (ft_str_cmp(key, "?") == 0)
	{
		*raw = ft_free(*raw);
		*raw = ft_itoa(get_exit_code());
		if (!*raw)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	*raw = ft_free(*raw);
	if (*key_value)
	{
		*raw = ft_strdup((*key_value)->value);
		if (!*raw)
			return (MALLOC_ERROR);
	}
	else
	{
		*raw = ft_calloc(sizeof(char), 1);
		if (!*raw)
			return (MALLOC_ERROR);
		(*raw)[0] = '\0';
	}
	return (SUCCESS);
}
