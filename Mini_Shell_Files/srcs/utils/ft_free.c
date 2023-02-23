//
// Created by rbonneva on 2/20/23.
//

#include <stdlib.h>
#include "../../incs/mini_shell.h"

void	*ft_free(void *pt)
{
	if (pt)
		free(pt);
	return (NULL);
}

void	*free_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
		split[i] = ft_free(split[i]);
	split = ft_free(split);
	return (NULL);
}
