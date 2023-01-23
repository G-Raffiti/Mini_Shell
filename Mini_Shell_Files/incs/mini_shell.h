/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:29:33 by rbonneva          #+#    #+#             */
/*   Updated: 2023/01/23 20:14:49 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../../Lib_List_Double/incs/ft_lstd.h"

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

typedef struct s_cmd
{
	char			*path;
	char			**cmd;
	char			**args;
	t_bool			is_builtin;
	t_fd			*input;
	t_fd			*output;
}					t_cmd;

typedef struct s_mini_shell
{
	char			**env;
	char			**paths;
	t_lstd			*cmds;
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
void	initialize_mini_shell(t_mini_shell *mini_shell, int argc, char \
	**argv, char **env);

// LIST UTILS //////////////////////////////////////////////////////////////////
t_cmd	*get(t_lstd *lst);

#endif
