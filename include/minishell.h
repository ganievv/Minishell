/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:56:18 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/20 19:32:35 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
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
	DELIMITER, // what is it ???
	APPEND_DELIMITER, // REDIR_OUT + append mode
	DOUBLE_QUOTED, // why do we need it ???
	SINGLE_QUOTED, // why do we need it ???
	EXP_FIELD // expanding field
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
*	'echo hello >'
*	bash: syntax error near unexpected token `newline'
*
*
*
*
*
*
*
*/

/*------------executer-----------*/

void	handle_signal(int signal);


/*------------builtins-----------*/
int		ft_pwd(char **args);
int		ft_cd(char **args);

#endif