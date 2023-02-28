#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../../Lib_List_Double/incs/ft_lstd.h"
# include "../../Lib_FT/incs/libft.h"
# include "error.h"
# include "debug.h"

/// IDIENTIFIER EXPORT /////////////////////////////////////////////////////////
# define INV_ID	" !#$%&()*+-.<>=:;`/'\\\"@{}[]^|~\n_"
# define INV_ID_EXPORT	" !#$%&()*+-.<>=:;`/\\'\"@{}[]^|~\n?"

/// DEFINE /////////////////////////////////////////////////////////////////////
# define PWD_PATH_SIZE 4096
# define PROMPT "ms "

# define SPLIT_COUNT 101
# define FILL_SPLIT_ARGS 102
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
#  define T_BOOL

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

# endif

typedef enum e_chevron
{
	PIPE_REDIR,
	IN_REDIR,
	HERE_DOC_REDIR,
	HERE_DOC_QUOTE_REDIR,
	OUT_REDIR,
	APPEND_REDIR,
}	t_chevron;

/// STRUCTURES /////////////////////////////////////////////////////////////////
typedef struct s_dollar
{
	char			quote;
	char			*raw_cmd;
	char 			*here_doc;
	int				prev_is_arg;
	int				start_dol;
	int				len_prev;
	int				nbr;
}					t_dollar;

typedef struct s_here_docs
{
	int 			pipe_h[2];
	char 			*limiter;
	t_bool			have_to_expand;
}					t_here_docs;

typedef struct s_fd
{
	int				fd;
	char			*name;
	int				error;
	t_chevron		type;
	t_lstd			*here_docs;
}					t_fd;

typedef struct s_env_arg
{
	char			*key;
	char			*value;
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
	t_bool			exported;
}					t_mini_shell;

/******************************************************************************/
/********************************   ENV   *************************************/
/******************************************************************************/

// ENV /////////////////////////////////////////////////////////////////////////
t_error		get_env(t_mini_shell *ms, char **env);
t_error		get_export_env(t_mini_shell *ms);

// MODIF_ENV ///////////////////////////////////////////////////////////////////
t_error		add_or_replace_in_chosen_env(t_mini_shell *ms, char *key,
				char *new_value, int which_env);
t_error		replace_in_chosen_env(t_mini_shell *ms, char *key,
				char *new_value, int which_env);
t_error		add_in_chosen_env(t_mini_shell *ms, char *key,
				char *value, int which_env);

/******************************************************************************/
/*******************************   EXEC   *************************************/
/******************************************************************************/

// EXEC ////////////////////////////////////////////////////////////////////////
t_error		exec_cmds(t_mini_shell *ms);
void		execve_cmd(t_mini_shell *ms, t_cmd *cmd);

// EXEC PIPELINE ///////////////////////////////////////////////////////////////
void		exec_pipeline(t_mini_shell *ms, t_lstd *current);

// EXEC_ERROR //////////////////////////////////////////////////////////////////
t_error		permission_denied(t_mini_shell *ms, t_cmd *cmd);
void		error_exec(t_mini_shell *ms, t_cmd *cmd);
void		wait_exit_status(t_mini_shell *ms, t_lstd *current);

// SIGNALS /////////////////////////////////////////////////////////////////////
void		set_interactiv_signals(void);
void		set_here_doc_signals(void);
void		set_exec_signals(void);

// SIGNALS HANDLER /////////////////////////////////////////////////////////////
void		here_doc_handler(int signum);
void		interactiv_handler(int signum);
void		exec_handler(int signum);

// HERE_DOCS ///////////////////////////////////////////////////////////////////
t_error		here_docs(t_mini_shell *ms, t_lstd *current);

// EXPAND_HERE_DOC /////////////////////////////////////////////////////////////
t_error		expand_here_doc(t_mini_shell *ms, char **here_doc, t_here_docs *here);

/******************************************************************************/
/*******************************   BUILTIN   **********************************/
/******************************************************************************/

// BUILTIN /////////////////////////////////////////////////////////////////////
t_error		exec_builtin(t_mini_shell *ms, t_cmd *cmd, t_bool in_pipe);

// BUILTINS FUNCTIONS //////////////////////////////////////////////////////////
t_error		ft_cd(t_mini_shell *ms, t_cmd *cmd);
t_error		ft_echo(t_cmd *cmd);
t_error		ft_exit(t_mini_shell *ms, t_cmd *cmd);
t_error		ft_pwd(void);
t_error		ft_env(t_mini_shell *ms);
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
t_error		check_line(t_mini_shell *ms, char *line);
t_error		parse_error(t_mini_shell *ms, char *error_msg, int error_code);

// GET CMD /////////////////////////////////////////////////////////////////////
t_error		get_cmd(t_cmd *cmd);
char		*str_dup_no_quote(char *line, size_t len);

// GET PATH ////////////////////////////////////////////////////////////////////
t_error		get_path(t_mini_shell *ms, t_cmd *cmd);
t_error		get_all_paths(t_mini_shell *ms, t_lstd *env_dict);

// GET RAW CMD /////////////////////////////////////////////////////////////////
char		**split_pipe(char *line);

// READ_LINE ///////////////////////////////////////////////////////////////////
char		*read_line(void);

// REPLACE_DOLLARS /////////////////////////////////////////////////////////////
t_error		replace_dollars(t_mini_shell *ms, t_cmd *cmds);
t_error		fill_end_raw(t_cmd *cmds, char **splited_raw);
t_error		create_final_raw(t_cmd **cmd, int final_len);
void		replace_dollar_before_quotes(t_cmd *cmd);
t_error		get_key_and_replace(char **raw, t_env_arg **key_value, char *key);
void		get_pair_key_value(t_mini_shell *ms, t_lstd *dict,
				t_env_arg **key_value, char *key);
void		check_secial_char(char *quote, int *prev_is_arg,
				int *i, char *raw_cmd);
int			check_id_and_count_prev(t_dollar *dlr, int which_function, int
				*split_len, int i);

// REPLACE TILDE ///////////////////////////////////////////////////////////////
t_error		replace_tilde(t_mini_shell *ms, t_cmd *cmd);
int			count_part_tilde(char *raw);
t_error		fill_split_tilde(char **split, char *raw);

// SET BUILTIN /////////////////////////////////////////////////////////////////
void		set_builtin(t_cmd *cmd);

// OPEN FILES //////////////////////////////////////////////////////////////////
t_error		open_files(t_mini_shell *ms, t_cmd *cmd);
t_error		extract_file_name(t_mini_shell *ms, char *str, t_chevron *type,
				char **file_name);

/******************************************************************************/
/*******************************   UTILS   ************************************/
/******************************************************************************/

// CHECK_FUNC //////////////////////////////////////////////////////////////////
int			valid_id_dollars(char c);
int			valid_id_export(char c);
int			is_not_alpha(char c);

// CLOSE ALL FILES /////////////////////////////////////////////////////////////
void		close_all_files(t_mini_shell *ms);

// DICT ////////////////////////////////////////////////////////////////////////
t_error		change_value_envs(t_env_arg *content, char *new_value);
int			find_in_dict(void *content, void *ref);
int			find_in_dict_sorted(void *content, void *ref);

// REGEN ENV ///////////////////////////////////////////////////////////////////
char		**regen_env(void);
t_error		increase_shell_lvl(t_mini_shell *ms);

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
void		free_cmd_void(void *pt_cmd);
void		*free_mini_shell(t_mini_shell *ms);
void		*free_dict(void *pt);

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
void		initialize_struct_dollar(t_dollar *dlr, t_cmd *cmds, \
														char **here_doc);

// DICT UTILS //////////////////////////////////////////////////////////////////
t_error		fill_dict_element(t_env_arg **dict, char *key, char *value);
t_error		fill_refreshed_env(t_lstd *current, char **str, int which_env);

// SAFE FUNC ///////////////////////////////////////////////////////////////////
void		safe_fork(t_mini_shell *ms, t_cmd *cmd, char *msg);
void		safe_pipe(t_mini_shell *ms, int pipes[2], char *msg);
void		safe_close(t_mini_shell *ms, int fd, char *msg);
void		safe_dup2(t_mini_shell *ms, int fd, int std, char *msg);
int			safe_dup(t_mini_shell *ms, int std, char *msg);

/******************************************************************************/
/*******************************   OTHERS   ***********************************/
/******************************************************************************/

// EXIT CODE ///////////////////////////////////////////////////////////////////
int			get_exit_code(void);
void		set_exit_code(int value);

// EXIT ////////////////////////////////////////////////////////////////////////
int			end_child(t_mini_shell *ms, t_cmd *cmd, int error_code, char *msg);
int			end_child_arg(t_mini_shell *ms, t_cmd *cmd, int code, char *msg);
t_error		exit_malloc(t_mini_shell *ms, char *msg);
t_error		exit_end_program(t_mini_shell *ms, int exit_code);
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
t_bool		test_mode(void);
void		set_test_mode(void);
int			test_minishell(char *line, t_mini_shell *ms);

char		**ft_strtab_dup(char **tab_to_dup);

#endif
