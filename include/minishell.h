/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:29:18 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 18:05:48 by sganiev          ###   ########.fr       */
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
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

# define BUILTIN_NUM 7

/*--------------------------token_types-------------------------*/
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

/*--------------------------tokens_list-------------------------*/
typedef struct s_token
{
	char			*token_start;
	int				len;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/*-------------------------commands_list------------------------*/
typedef struct s_pipe_group
{
	char				*command;
	char				**args;
	char				*file_in;
	char				*file_out;
	int					redir_in;
	int					redir_out;
	int					mode_in;
	int					mode_out;
	char				**argv;    //|
	char				*cmd_path; //|-> this 2 vars we need in executor
	struct s_group_cmd	*next;
}	t_pipe_group;

/*------------------all_important_project_vars------------------*/
typedef struct s_msh
{
	char			*input;
	t_token			*tokens;
	t_pipe_group	*cmds;
	int				cmds_num;
	char			**envp;
	int				last_exit_status;
	int				*pids;
	int				**pipes;
	char			*builtin_names[BUILTIN_NUM + 1];
	int				(*builtin_ptrs[BUILTIN_NUM + 1])(char **args,
			char ***envp);
}	t_msh;

/*-----------------------------main-----------------------------*/

/*---------------------------executor---------------------------*/
int				exec_all_cmds(t_msh *info);

/*---------------------------builtins---------------------------*/
int				ft_pwd(char **args, char ***envp);
int				ft_cd(char **args, char ***envp);
int				ft_echo(char **args, char ***envp);
int				ft_exit(char **args, char ***envp);
int				ft_export(char **args, char ***envp);
int				ft_unset(char **args, char ***envp);
int				ft_env(char **args, char ***envp);

/*--------------------------utils_exec--------------------------*/
int				count_args(char **args);
int				is_nbr(char *arg);
int				is_valid_exit_range(char *nbr);
long long		ft_atoll(char *str);
int				count_cmds(t_pipe_group *cmds);
void			init_builtin_names(char **builtin_names);
void			init_builtin_ptrs(int (**builtin_ptrs)(char **, char ***));
int				is_export_arg_valid(char *arg);
char			**copy_arr_str(char **src);
int				search_env_var(char *var_to_find, char **envp);
int				is_cmd_builtin(char *cmd, t_msh *info);
char			*search_exec_dir(char *file, char *path_env_v);
char			*search_cmd_path(char *cmd, t_msh *info);
char			**args_to_argv(char **args, char *cmd_path);
int				pipes_create(t_msh *info, int cmds_num);
void			make_pipes_redir(t_msh *info, int cmd_index);
void			make_files_redir(t_pipe_group *cmd);
void			wait_for_processes(t_msh *info, int cmds_num);
void			free_arr_str(char **arr);
void			free_arr_int(int **arr, int num);
void			free_pids_and_pipes(t_msh *info);
void			free_all_prog_vars(t_msh *info);
char			*print_env_vars(char **list);
void			change_or_add_env_var(char *var, char ***envp);

/*----------------lexer---------------------*/
t_token_type	token_find_type(char *str, int i, int len);
void			token_list(t_token **head, char *rl);
/*------------lexer-utils-one---------------*/
int				redir(char *str, int i);
int				is_quoted(char *str, int i);
int				is_d_quoted(char *str, int i);
/*------------lexer-utils-two---------------*/
int				ft_isquote_dquote(char c);
int				ft_isvar_dqoute(char *str, int i);
t_token			*token_new(char *rl, int i, int len);
void			ft_lstadd_back(t_token **lst, t_token *new);
/*------------lexer-utils-three---------------*/
int				simple_seperators(char c);
void			isspace_skip(char *rl, int *i);
void			len_quoted(char *rl, int *len);
void			len_var(char *rl, int *len);
int				len_words(char *rl, int *len);
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/
/*fgjk*/

void			handle_signal(int signal);

#endif