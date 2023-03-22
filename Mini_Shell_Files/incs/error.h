/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:01:03 by rbonneva          #+#    #+#             */
/*   Updated: 2023/03/22 16:15:14 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNTAX_PIPE		"syntax error near unexpected token `|'"
# define SYNTAX_REDIR_OUT	"syntax error near unexpected token `>'"
# define SYNTAX_REDIR_IN	"syntax error near unexpected token `<'"
# define SYNTAX_REDIR_2OUT	"syntax error near unexpected token `>>'"
# define SYNTAX_REDIR_2IN	"syntax error near unexpected token `<<'"
# define SYNTAX_REDIR_3IN	"syntax error near unexpected token `<<<'"
# define SYNTAX_NEWLINE		"syntax error near unexpected token `newline'"
# define COMMAND_NOT_FOUND	"command not found"
# define QUOTE_ERROR		"syntax error quote not closed"
# define INVALID_IDENTIFIER	"not a valid identifier"
# define TOO_MANY_ARGS		"too many arguments"
# define NUMERIC_ARGS		"numeric argument required"
# define HOME_NOT_SET		"HOME not set"
# define OLDPWD_NOT_SET		"OLDPWD not set"
# define FILENAME_REQUIERED	"filename argument required"
# define IS_DIRECTORY		"Is a directory"
# define PERMISSION_DENIED	"Permission denied"
# define NO_FILE			"No such file or directory"
# define AMBIGUOUS_REDIRECT	"ambiguous redirect"
# define MALLOC_FAILED		"Memory allocation failed"
# define NO_PARENT "error retrieving current directory: getcwd: cannot \
						access parent directories: No such file or directory"
# define QUOTE			'\"'
# define S_QUOTE		'\''
# define FUNCTION_FAILUR	255

#endif
