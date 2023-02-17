//
// Created by rbonneva on 09/02/23.
//

#include "../../incs/mini_shell.h"

char	*strjoin_split(char **split, char *sep)
{
	size_t	len;
	int		i;
	char	*str;
	size_t	sep_len;

	len = 1;
	i = -1;
	sep_len = ft_strlen(sep);
	while (split[++i])
	{
		len += ft_strlen(split[i]);
		if (split[i + 1])
			len += sep_len;
	}
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		ft_strcat(str, split[i]);
		if (split[i + 1])
			ft_strcat(str, sep);
	}
	return (str);
}

t_bool is_n(char *str)
{
	if (str[0] != '-' && (!str[1] || str[1] != 'n'))
		return (FALSE);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_error	ft_echo(t_cmd *cmd)
{
	t_bool	newline;
	char	**split;
	char	*str;

	newline = TRUE;
	split = &cmd->cmd[1];
	while (*split && is_n(*split))
	{
		split++;
		newline = FALSE;
	}
	str = strjoin_split(split, " ");
	if (!str)
		return (MALLOC_ERROR);
	if (newline)
		printf("%s\n", str);
	else
		printf("%s", str);
	str = ft_free(str);
	set_exit_code(0);
	return (SUCCESS);
}