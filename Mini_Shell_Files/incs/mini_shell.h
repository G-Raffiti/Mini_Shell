
#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../../Lib_List_Double/incs/ft_lstd.h"
# include "../../Lib_FT/incs/libft.h"
# define PROMPT "ms_$"
/////		IDIENTIFIER EXPORT /////
# define INV_ID	"! # $ % & ( ) * + - . < > = : ; ` / ' \" @ { } [ ] ^ | ~ \n"

# ifndef T_ERROR
#  define T_ERROR



typedef enum e_error
{
	MALLOC_ERROR = -1,
	ERROR = 0,
	SUCCESS = 1,
}	t_error;

# endif

# ifndef T_BOOL
# define T_BOOL

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

# endif



/////////////////////////////////////
typedef enum e_chevron
{
	ERROR_CHT,
	IN_CHT,
	HERE_DOC_CHT,
	OUT_CHT,
	APPEND_CHT,
}	t_chevron;

typedef struct s_fd
{
	int				fd;
	char			*name;
	int				error;
}					t_fd;

typedef struct s_env_arg
{
	char			*key;
	char 			*value;
}					t_env_arg;

typedef struct s_cmd
{
	int				pid;
	char			*raw_cmd;
	t_bool			*is_dollar;
	char			*path;
	char			**cmd;
	t_fd			*input;
	t_fd			*output;
	t_bool			is_builtin;
	t_bool			is_valid;
}					t_cmd;

typedef struct s_mini_shell
{
	char			**env;
	t_lstd			*env_dict;
	char			**paths;
	t_lstd			*cmds;
	int				pipe[2];
}					t_mini_shell;

#ifndef G_EXIT_CODE
#define G_EXIT_CODE

extern int	g_exit_code;

#endif

// NEW STRUCT //////////////////////////////////////////////////////////////////
t_error		new_fd(t_fd **fd);
t_error		new_cmd(t_cmd **cmd);
t_error		new_mini_shell(t_mini_shell **ms);
t_error		new_env_args(t_env_arg **env_dict);

// FREE STRUCT /////////////////////////////////////////////////////////////////
void		*ft_free(void *pt);
void		*free_split(char **split);
void		*free_fd(t_fd *fd);
void		*free_cmd(t_cmd *cmd);
void		*free_mini_shell(t_mini_shell *ms);

// EXIT ////////////////////////////////////////////////////////////////////////
int			get_exit_code(void);
void		set_exit_code(int value);
t_error		exit_malloc(t_mini_shell *mini_shell, char *msg);
t_error		exit_end_program(t_mini_shell *ms);
void		exit_error(t_mini_shell *ms, int error_code, char *msg);
void		exit_child(t_cmd *cmd, int error_code, char *msg);

// LIST UTILS //////////////////////////////////////////////////////////////////
t_cmd		*get(t_lstd *lst);
t_env_arg	*get_env_dict(void *content);
void		clear_cmds(t_lstd **lst, void *(*free_fct)(t_cmd *));

// PARSING /////////////////////////////////////////////////////////////////////
int			set_quote_state(char c, char *quote);
t_error		parse_line(t_mini_shell *ms, char *line);

// ENV /////////////////////////////////////////////////////////////////////////
int			find_in_dict(void *content, void *ref);
void		get_env(t_mini_shell *ms, char **env);
t_error		get_all_paths(t_mini_shell *ms, t_lstd *env_dict);

// PARSING - READ_LINE /////////////////////////////////////////////////////////
char		*read_line(void);

// PARSING - CHECK LINE ////////////////////////////////////////////////////////
t_error		check_line(char *line);
t_error		parse_error(char *error_msg, int error_code);

// PARSING - GET RAW CMD ///////////////////////////////////////////////////////
char		**split_pipe(char *line);

// PARSING - GET CMD ///////////////////////////////////////////////////////////
t_error		get_cmd(t_cmd *cmd);

// PARSING - OPEN FILES ////////////////////////////////////////////////////////
t_error		open_files(t_mini_shell *ms, t_cmd *cmd);

// PARSING - GET PATH //////////////////////////////////////////////////////////
t_error		get_path(t_mini_shell *ms, t_cmd *cmd);

// PARSING - REPLACE_DOLLARS
t_error		replace_dollars(t_mini_shell *ms, t_cmd *cmds);
// PARSING - SET BUILTIN ///////////////////////////////////////////////////////
void		set_builtin(t_lstd *current);

// SAFE FUNC ///////////////////////////////////////////////////////////////////
void		safe_fork(t_mini_shell *ms, t_cmd *cmd, char *msg);
void		safe_pipe(t_mini_shell *ms, char *msg);
void		safe_close(t_mini_shell *ms, int fd, char *msg);
void		safe_dup2(t_mini_shell *ms, int fd, int std, char *msg);
void		safe_rev_dup2(t_mini_shell *ms, int std, int fd, char *msg);

// EXEC ////////////////////////////////////////////////////////////////////////
t_error		exec_cmds(t_mini_shell *ms);

// TEST ////////////////////////////////////////////////////////////////////////
void	debug_cmd(t_cmd *cmd);
void	debug_all_cmds(t_mini_shell *ms);
void	debug_mini_shell(t_mini_shell *ms);
void	debug_fd(t_mini_shell *ms, t_cmd *cmd);

#endif
