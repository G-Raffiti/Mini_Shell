
#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../../Lib_List_Double/incs/ft_lstd.h"
# include "../../Lib_FT/incs/libft.h"
# include "error.h"
# include "debug.h"
/// IDIENTIFIER EXPORT /////////////////////////////////////////////////////////
# define INV_ID	"! # $ % & ( ) * + - . < > = : ; ` / ' \\ \" @ { } [ ] ^ | ~ \n _"
# define INV_ID_EXPORT	"! # $ % & ( ) * + - . < > = : ; ` /  \\ ' \" @ { } [ ] ^ | ~ \n ?"

/// DEFINE /////////////////////////////////////////////////////////////////////
# define PWD_PATH_SIZE 4096
# define PROMPT "ms "

/// ENUMS //////////////////////////////////////////////////////////////////////
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

typedef enum e_chevron
{
	ERROR_CHT,
	IN_CHT,
	HERE_DOC_CHT,
	OUT_CHT,
	APPEND_CHT,
}	t_chevron;

/// STRUCTURES /////////////////////////////////////////////////////////////////
typedef struct s_fd
{
	int				fd;
	char			*name;
	int				error;
	// HEREDOC :
	char			*limiter;
	int				here_doc_pipe[2];
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
	char			*path;
	char			**cmd;
	t_fd			*input;
	t_fd			*output;
	t_bool			is_builtin;
	t_bool			is_valid; //TODO => delete
	t_bool			need_fork;
}					t_cmd;

typedef struct s_mini_shell
{
	char			**env;
	char			**env_sort;
	t_lstd			*env_dict;
	t_lstd			*env_sort_dict;
	char			**paths;
	t_lstd			*cmds;
	int				pipe[2];
	int				stds[2];
	t_bool 			exported;
}					t_mini_shell;

/******************************************************************************/
/********************************   ENV   *************************************/
/******************************************************************************/

// ENV /////////////////////////////////////////////////////////////////////////
t_error		get_env(t_mini_shell *ms, char **env);
t_error		get_export_env(t_mini_shell *ms);

// MODIF_ENV ///////////////////////////////////////////////////////////////////
t_error		add_or_replace_in_chosen_env(t_mini_shell *ms, char *key, char *new_value, int which_env);
t_error		replace_in_chosen_env(t_mini_shell *ms, char *key, char *new_value, int which_env);
t_error		add_in_chosen_env(t_mini_shell *ms, char *key, char *value, int which_env);

/******************************************************************************/
/*******************************   EXEC   *************************************/
/******************************************************************************/

// EXEC ////////////////////////////////////////////////////////////////////////
t_error		exec_cmds(t_mini_shell *ms);

// SIGNALS /////////////////////////////////////////////////////////////////////
void		set_interactiv_signals();
void		set_exec_signals();


/******************************************************************************/
/*******************************   BUILTIN   **********************************/
/******************************************************************************/

// BUILTIN /////////////////////////////////////////////////////////////////////
t_error		exec_builtin(t_mini_shell *ms, t_cmd *cmd, t_bool in_pipe);

// BUILTIN ERRORS //////////////////////////////////////////////////////////////
void		builtin_error_env(char *arg, int error_code, char *msg);
void		builtin_error_export(char *arg, int error_code, char *msg);

// BUILTINS FUNCTIONS //////////////////////////////////////////////////////////
t_error		ft_cd(t_mini_shell *ms, t_cmd *cmd);
t_error		ft_echo(t_cmd *cmd);
t_error		ft_exit(t_mini_shell *ms);
t_error		ft_pwd(void);
t_error		ft_env(t_mini_shell *ms, t_cmd *cmd, int in_pipe);
t_error		ft_export(t_mini_shell *ms, t_cmd *cmd, int in_pipe);
t_error		ft_unset(t_mini_shell *ms, t_cmd *cmd, int in_pipe);

/******************************************************************************/
/*******************************   PARSING   **********************************/
/******************************************************************************/

// PARSING /////////////////////////////////////////////////////////////////////
int			set_quote_state(char c, char *quote);
t_error		parse_line(t_mini_shell *ms, char *line);

// CHECK LINE //////////////////////////////////////////////////////////////////
t_bool		is_empty_line(char *line);
t_error		check_line(char *line);
t_error		parse_error(char *error_msg, int error_code);

// GET CMD /////////////////////////////////////////////////////////////////////
t_error		get_cmd(t_cmd *cmd);

// GET PATH ////////////////////////////////////////////////////////////////////
t_error		get_path(t_mini_shell *ms, t_cmd *cmd);
t_error		get_all_paths(t_mini_shell *ms, t_lstd *env_dict);

// GET RAW CMD /////////////////////////////////////////////////////////////////
char		**split_pipe(char *line);

// READ_LINE ///////////////////////////////////////////////////////////////////
char		*read_line(void);

// REPLACE_DOLLARS /////////////////////////////////////////////////////////////
t_error		replace_dollars(t_mini_shell *ms, t_cmd *cmds);
t_error		replace_dollar_before_quotes(t_cmd *cmd);

// SET BUILTIN /////////////////////////////////////////////////////////////////
void		set_builtin(t_cmd *cmd);

// OPEN FILES //////////////////////////////////////////////////////////////////
t_error		open_files(t_mini_shell *ms, t_cmd *cmd);

/******************************************************************************/
/*******************************   UTILS   ************************************/
/******************************************************************************/

// CHECK_FUNC //////////////////////////////////////////////////////////////////
int			valid_id_dollars(char c);
int			valid_id_export(char c);
int			is_not_alpha(char c);

// DICT ////////////////////////////////////////////////////////////////////////
t_error		change_value_envs(t_env_arg *content, char *new_value);
int			find_in_dict(void *content, void *ref);
int			find_in_dict_sorted(void *content, void *ref);

// ENV /////////////////////////////////////////////////////////////////////////
t_error		fill_export_env(t_mini_shell *ms);
t_error		fill_env(t_mini_shell *ms);
t_error		refresh_env(t_mini_shell *ms);
t_error		refresh_export_env(t_mini_shell *ms);

// ENV_TYPE ////////////////////////////////////////////////////////////////////
t_error		get_value_env_type(t_env_arg *content);
t_error		get_key_env_type(t_env_arg *content);
t_error		get_export_type(t_mini_shell *ms);

// FREE STRUCT /////////////////////////////////////////////////////////////////
void		*ft_free(void *pt);
void		*free_split(char **split);
void		*free_fd(t_fd *fd);
void		*free_cmd(t_cmd *cmd);
void		*free_mini_shell(t_mini_shell *ms);

// LIST UTILS //////////////////////////////////////////////////////////////////
t_cmd		*get(t_lstd *lst);
t_env_arg	*get_env_dict(void *content);
void		clear_cmds(t_lstd **lst, void *(*free_fct)(t_cmd *));
void		sort_dict(t_lstd **lst, int (*cmp)());
t_error		create_new_list_element(t_lstd **element, t_env_arg *dict);

// NEW STRUCT //////////////////////////////////////////////////////////////////
t_error		new_fd(t_fd **fd);
t_error		new_cmd(t_cmd **cmd);
t_error		new_mini_shell(t_mini_shell **ms);
t_error		new_env_arg(t_env_arg **env_dict);

// DICT UTILS //////////////////////////////////////////////////////////////////
t_error		fill_dict_element(t_env_arg **dict, char *key, char *value);
t_error		fill_refreshed_env(t_lstd *current, char **str, int which_env);

// SAFE FUNC ///////////////////////////////////////////////////////////////////
void		safe_fork(t_mini_shell *ms, t_cmd *cmd, char *msg);
void		safe_pipe(t_mini_shell *ms, char *msg);
void		safe_close(t_mini_shell *ms, int fd, char *msg);
void		safe_dup2(t_mini_shell *ms, int fd, int std, char *msg);
int			safe_dup(t_mini_shell *ms, int std, char *msg);

/*\\\\\\\\\\\\\\\\\\\\\\\\\\ OTHERS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

// EXIT CODE ///////////////////////////////////////////////////////////////////
int			get_exit_code(void);
void		set_exit_code(int value);

// EXIT ////////////////////////////////////////////////////////////////////////
int			end_child(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg);
t_error		exit_malloc(t_mini_shell *ms, char *msg);
t_error		exit_end_program(t_mini_shell *ms);
void		exit_error(t_mini_shell *ms, int error_code, char *msg);
void		exit_child(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg);

// DEBUG ///////////////////////////////////////////////////////////////////////
t_bool		debug_mod(void);
void		enable_debug(void);
void		debug(int ac, ...);
void		debug_cmd(t_cmd *cmd);
void		debug_all_cmds(t_mini_shell *ms);
void		debug_mini_shell(t_mini_shell *ms);
void		debug_fd(t_mini_shell *ms, t_cmd *cmd);

// TEST MODE ///////////////////////////////////////////////////////////////////
t_bool		test_mode();
void		set_test_mode();
int			test_minishell(char *line, t_mini_shell *ms);

char		**ft_strtab_dup(char **tab_to_dup);

#endif
