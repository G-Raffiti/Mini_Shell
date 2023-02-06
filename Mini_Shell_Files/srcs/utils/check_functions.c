//
// Created by aurel on 2/4/23.
//

#include "../../incs/mini_shell.h"

int	valid_id_dollars(char c)
{
	if (ft_contain(INV_ID, c) || c >= 127 || c == ' ')
		return (0);
	return (1);
}

int	valid_id_export(char c)
{
	if (ft_contain(INV_ID_EXPORT, c) || c >= 127 || c == ' ')
		return (0);
	return (1);
}

int	is_not_alpha(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}