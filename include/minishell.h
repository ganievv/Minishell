/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:56:18 by tnakas            #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/07/22 21:04:57 by tnakas           ###   ########.fr       */
=======
/*   Updated: 2024/07/22 21:02:01 by sganiev          ###   ########.fr       */
>>>>>>> d50fdac6ab9220c001db9034ad1bdd55fce95cbc
=======
/*   Updated: 2024/07/22 21:02:01 by sganiev          ###   ########.fr       */
>>>>>>> d50fdac6ab9220c001db9034ad1bdd55fce95cbc
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
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

void		handle_signal(int signal);


/*------------builtins-----------*/
int			ft_pwd(char **args);
int			ft_cd(char **args);
int			ft_echo(char **args);

/*------------utils-----------*/
int			count_args(char **args);
int			is_nbr(char *arg);
int			is_valid_exit_range(char *nbr);
long long	ft_atoll(char *str);
/*------------parser-utils-one---------------*/
int			ft_isdouble_lower_bigger(char *str, int i);
int			ft_issingle_pipe_lower_bigger(char c);
int			ft_issingle_quote(char *str, int i);
int			ft_isdouble_quote(char *str, int i);
int			ft_isvar(char c);
/*------------parser-utils-two---------------*/
int			ft_isvar_dqoute(char *str, int i);
t_token	*	token_new(char *content);
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
#endif