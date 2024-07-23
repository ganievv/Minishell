/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:29:18 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/23 15:25:39 by sganiev          ###   ########.fr       */
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

/*-----------parser-launch----------*/

// pipe grouping
// expansions ($)

typedef struct s_pipe_group
{
	char				*command;
	char				**args;
	char				*file;
	int					redir_fd;
	int					mode;
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
*/


/*-----------------------------main-----------------------------*/

/*---------------------------executor---------------------------*/
int				exec_all_cmds(t_pipe_group *groups, char **envp);

/*---------------------------builtins---------------------------*/
# define BUILTIN_NUM 7

int				ft_pwd(char **args);
int				ft_cd(char **args);
int				ft_echo(char **args);
int				ft_exit(char **args);
int				ft_export(char **args);
int				ft_unset(char **args);
int				ft_env(char **args);

/*--------------------------utils_exec--------------------------*/
int				count_args(char **args);
int				is_nbr(char *arg);
int				is_valid_exit_range(char *nbr);
long long		ft_atoll(char *str);
/*----------------lexer---------------------*/
t_token_type	token_find_type(char *str);
/*------------lexer-utils-one---------------*/
int				ft_isdouble_lower_bigger(char *str, int i);
int				ft_issingle_pipe_lower_bigger(char c);
int				ft_issingle_quote(char *str, int i);
int				ft_isdouble_quote(char *str, int i);
int				ft_isvar(char c);
/*------------lexer-utils-two---------------*/
int				ft_isvar_dqoute(char *str, int i);
t_token			*token_new(char *content);
void			ft_lstadd_back(t_token **lst, t_token *new);
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/

void			handle_signal(int signal);

#endif