//
// Created by rbonneva on 03/02/23.
//

int	g_exit_code;

void	set_exit_code(int value)
{
	g_exit_code = value;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}
