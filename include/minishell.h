/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:56:18 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/16 12:57:06 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

/*-----------lexer-launch-----------*/

typedef enum e_token_type
{
	WORD,
	SEP,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	DELIMITER,
	APPEND_DELIMITER,
	DOUBLE_QUOTED,
	SINGLE_QUOTED,
	EXP_FIELD
}	t_token_type;

typedef struct s_token
{
	char			*token_start;
	int				len;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// here we should handle heredoc

/*-----------parser-launch----------*/

// pipe grouping
// expansions ($)

typedef struct	s_pipe_group
{
	char				*command;
	char				**args;
	char				*file;    /* if file: NULL then no redir */
	int					redir_fd; /* 0: stdin; 1: stdout */
	int					mode;     /* 0: O_RDONLY, O_WRONLY, O_CREAT, O_APPEND  */
	struct s_group_cmd	*next;
}	t_pipe_group;

/*-----------error-checking---------*/
/*
*	'exit 3 c | echo "Hello"':
*	-bash: exit: too many arguments
*	Hello
*
*
*	'exit':
*				- check number of args (should be only 1)
*				- check if this 1 arg is a number
*
*	'export':
*
*	spaces between file name and command ?
*	<file.txt
*	> file.txt
*	<<stop
*	>>     file.txt
*
*/

/*------------executer-----------*/

void	handle_signal(int signal);

#endif