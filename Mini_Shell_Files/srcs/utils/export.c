#include "../../incs/mini_shell.h"

void	get_equal_char_pos(char *arg, int *pos)
{
	*pos = 0;
	while (arg[*pos] && arg[*pos] != '=')
		(*pos)++;
	if (*pos == (int)ft_strlen(arg))
		*pos = 0;
}
