
#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../../Lib_List_Double/incs/ft_lstd.h"
# include "../../Lib_FT/incs/libft.h"

# ifndef T_ERROR
#  define T_ERROR

typedef enum e_error
{
	MALLOC_ERROR = -1,
	ERROR = 0,
	SUCCESS = 1,
}	t_error;

# endif

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_fd
{
	int				fd;
	int				open_mode;
}					t_fd;

typedef struct s_arg_env
{
	char	*key;
	char	**value;
}	t_arg_env;

typedef struct s_cmd
{
	int				pid;
	char			*raw_cmd;
	char			*path;
	char			**cmd;
	char			**args_cmd;
	t_fd			*input;
	t_fd			*output;
	t_bool			is_builtin;
}					t_cmd;

typedef struct s_mini_shell
{
	char			**env;
	t_lstd			*env_lst;
	char			**paths;
	t_lstd			*cmds;
	int				pipe[2];
}					t_mini_shell;

// NEW STRUCT //////////////////////////////////////////////////////////////////
t_error	new_fd(t_fd *fd);
t_error	new_cmd(t_cmd *cmd);
t_error	new_mini_shell(t_mini_shell *mini_shell);

// FREE STRUCT /////////////////////////////////////////////////////////////////
void	*ft_free(void *pt);
void	*free_split(char **split);
void	*free_fd(t_fd *fd);
void	*free_cmd(t_cmd *cmd);
void	*free_mini_shell(t_mini_shell *mini_shell);

// EXIT ////////////////////////////////////////////////////////////////////////
t_error	exit_malloc(t_mini_shell *mini_shell);
t_error	exit_end_program(t_mini_shell *mini_shell);

// INITIALIZE //////////////////////////////////////////////////////////////////
void	set_env(t_mini_shell *mini_shell, char **env);

// LIST UTILS //////////////////////////////////////////////////////////////////
t_cmd	*get(t_lstd *lst);
t_arg_env	*get_arg_env(void *content);

// PARSING
char	**split_pipe(char *line);
t_fd	*chevron(t_lstd *current, char *file_path, char *chevron_type);
#endif
