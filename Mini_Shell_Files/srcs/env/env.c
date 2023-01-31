
#include "../incs/mini_shell.h"

void	get_env(t_mini_shell *mini_shell, char **env)
{
	mini_shell->env = env;

	// TODO [Aurel]: create list of env_args (char* key / char** value)
	// ATTENTION garde les / a la fin des PATH
}

void	set_env(t_mini_shell *ms, char **env)
{
	(void)ms;
	(void)env;
}
// TODO [Aurel]: synchro list env to char** env
// TODO [Aurel]: synchro char** env to list env