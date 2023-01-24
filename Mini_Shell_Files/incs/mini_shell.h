
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

typedef struct s_env_arg
{
	char	*key;
	char	**value;
}	t_env_arg;

typedef struct s_cmd
{
	int				pid;
	char			*raw_cmd;
	char			*path;
	char			**cmd;
	t_fd			*input;
	t_fd			*output;
	t_bool			is_builtin;
}					t_cmd;

typedef struct s_mini_shell
{
	char			**env;
	t_lstd			*env_dict;
	char			**paths;
	t_lstd			*cmds;
	int				pipe[2];
}					t_mini_shell;

int	g_exit_code;

// NEW STRUCT //////////////////////////////////////////////////////////////////
t_error		new_fd(t_fd *fd);
t_error		new_cmd(t_cmd *cmd);
t_error		new_mini_shell(t_mini_shell *mini_shell);

// FREE STRUCT /////////////////////////////////////////////////////////////////
void		*ft_free(void *pt);
void		*free_split(char **split);
void		*free_fd(t_fd *fd);
void		*free_cmd(t_cmd *cmd);
void		*free_mini_shell(t_mini_shell *mini_shell);

// EXIT ////////////////////////////////////////////////////////////////////////
t_error		exit_malloc(t_mini_shell *mini_shell);
t_error		exit_end_program(t_mini_shell *mini_shell);

// INITIALIZE //////////////////////////////////////////////////////////////////
void		set_env(t_mini_shell *mini_shell, char **env);

// LIST UTILS //////////////////////////////////////////////////////////////////
t_cmd		*get(t_lstd *lst);
t_env_arg	*get_env_dict(void *content);
void		clear_cmds(t_lstd **cmds);

// PARSING /////////////////////////////////////////////////////////////////////
t_bool		is_quote_error(char *line);
t_bool		is_chevron_error(char *line);
t_error		parse_error(char *error_msg, int error_code);
t_error		parse_line(t_mini_shell *mini_shell, char *line);
int			find(void *content, void *ref);
char		*get_env_value(char *key, t_lstd *env_dict);
int			set_quote_state(char c, char *quote);
t_fd		*chevron(t_lstd *current, char *file_path, char *chevron_type);

// PARSING - RAW CMD ///////////////////////////////////////////////////////////
char		**split_pipe(char *line);

// EXEC ////////////////////////////////////////////////////////////////////////
void		exec_cmd_child(t_mini_shell *mini_shell, t_lstd *current);
void		make_child(t_mini_shell *mini_shell, t_lstd *current);
t_error		exec_cmds(t_mini_shell *mini_shell);

#endif
