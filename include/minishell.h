/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:51:39 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 22:40:33 by tnakas           ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

# define BUILTIN_NUM 7

/*--------------------------exit_codes-------------------------*/
# define CMD_NOT_FOUND 127
# define SIGINT_ESTATUS 130
# define SIGQUIT_ESTATUS 131

/*----------------------------colors---------------------------*/
# define GRAY "\x1b[90m"
# define RESET "\x1b[0m"

/*--------------------------token_types-------------------------*/
typedef enum e_token_type
{
	WORD,
	SPC,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	HEREDOC,
	APPEND_DELIMITER,
	D_QUOTED,
	S_QUOTED,
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

typedef struct s_h_token
{
	int	i;
	int	start;
	int	len;
}	t_h_token;

typedef struct s_rdr_const
{
	int		l;
	char	**envp;
}	t_rdr_const;
/*----------------expander-helper-struct------------------------*/
typedef struct s_exp_helper
{
	char		*temp;
	char		*var;
	size_t		len;
	char		*end;
	char		*result;
	char		*start;
}	t_exp_helper;
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
	char				*heredoc_strs;
	bool				is_heredoc_in;
	char				**argv;
	char				*cmd_path;
	struct s_pipe_group	*next;
}	t_pipe_group;

/*------------------all_important_project_vars------------------*/

typedef struct s_msh	t_msh;

struct s_msh
{
	char			*input;
	t_token			*tokens;
	t_token			*ready;
	t_pipe_group	*cmds;
	int				cmds_num;
	char			**envp;
	int				last_exit_status;
	int				*pids;
	int				**pipes;
	char			*builtin_names[BUILTIN_NUM + 1];
	int				(*builtin_ptrs[BUILTIN_NUM + 1])(char **args,
			char ***envp, t_msh *info);
};

/*--------------------------utils_main--------------------------*/
void			t_msh_init(t_msh *info, char **envp);
void			print_header(void);
void			clear_screen(void);
int				is_input_empty(char *input);
void			handle_shlvl_var(t_msh *info);
void			init_builtin_names(char **builtin_names);
void			init_builtin_ptrs(int (**builtin_ptrs)(char **,
						char ***, t_msh *));
char			**copy_arr_str(char **src);
void			process_input(t_msh *info, t_rdr_const rdr);
void			process_pipeline(t_msh *info, t_rdr_const rdr, t_token **ready);
/*---------------------------builtins---------------------------*/
int				ft_pwd(char **args, char ***envp, t_msh *info);
int				ft_cd(char **args, char ***envp, t_msh *info);
int				ft_echo(char **args, char ***envp, t_msh *info);
int				ft_exit(char **args, char ***envp, t_msh *info);
int				ft_export(char **args, char ***envp, t_msh *info);
int				ft_unset(char **args, char ***envp, t_msh *info);
int				ft_env(char **args, char ***envp, t_msh *info);
/*--------------------------utils_exec--------------------------*/

/*---------------------------executor---------------------------*/
void			exec_all_cmds(t_msh *info);
int				count_args(char **args);
int				count_cmds(t_pipe_group *cmds);
int				is_cmd_builtin(char *cmd, t_msh *info);
char			*search_exec_dir(char *file, char *path_env_v);
char			*search_cmd_path(char *cmd, t_msh *info);
char			**args_to_argv(char **args, char *cmd_path);
void			wait_for_processes(t_msh *info, int cmds_num);
void			close_all_pipes(int **pipes, int len);
char			*str_to_lower_case(const char *cmd);
char			*make_absolute_path(char *dir, char *file);
void			print_cmd_not_found(char *cmd);
void			reset_signals(void);
int				is_cmd_present_one_cmd(t_msh *info);
void			is_cmd_present_multiple_cmds(t_pipe_group *cmd);

/*---------------------------cleanup----------------------------*/
void			free_str(char **str);
void			free_arr_str(char ***arr);
void			free_arr_int(int **arr, int num);
void			free_pids_and_pipes(t_msh *info);
void			free_all_prog_vars(t_msh *info);
/*---------------------------env_vars---------------------------*/
int				search_env_var(char *var_to_find, char **envp);
char			*take_env_var_value(char *var);
char			*take_env_var_name(char *var);
/*-----------------------------pipes----------------------------*/
int				pipes_create(t_msh *info, int cmds_num);
void			make_pipes_redir(t_msh *info, int cmd_index);
/*--------------------------files_redir-------------------------*/
int				make_files_redir(t_pipe_group *cmd);
int				*save_io_fds(t_pipe_group *cmd);
void			restore_io_fds(int *fds, t_pipe_group *cmd);
/*-----------------------------exit-----------------------------*/
int				is_nbr(char *arg);
int				is_valid_exit_range(char *nbr);
long long		ft_atoll(char *str);
void			prepare_exit(t_msh *info, char **exit_arg);
/*----------------------------export----------------------------*/
void			double_array_sort(char **array, int size);
int				is_export_arg_valid(char *arg);
void			print_env_vars(char **list);
void			change_or_add_env_var(char *var, char ***envp);
/*-----------------------------unset----------------------------*/
void			remove_env_var(char *var, char ***envp);
int				is_unset_arg_valid(char *arg);
/*------------------------------cd------------------------------*/
void			update_pwd_var(char ***envp);
void			update_oldpwd_var(char ***envp);
int				check_special_cd_options(char **dir, char **envp);
void			print_err_for_cd(char *dir);
/*-----------------------------echo-----------------------------*/
bool			check_cmd_flag(char flag, char ***args);
/*----------------lexer---------------------*/
int				tokenize(char *input, t_token **head);
/*------------lexer-utils-one---------------*/
int				is_seperator(char c);
int				is_quote(char c);
t_token_type	token_type(char *str, int len);
/*------------lexer-utils-two---------------*/
t_token			*token_create(char *start, int len, t_token_type type);
t_token			*token_create_preexp(char *start, int len, t_token_type type);
char			*token_content_extract(t_token *token, int current_len);
void			token_lstadd(t_token **head, t_token *new_token);
/*-------------lexer-utils-three--------------*/
void			pipe_error_start(char *input);
int				pipe_error_end(t_token **head);
void			token_free(t_token **head);
void			print_tokens(t_token *head);
/*--------------lexer-utils-four---------------*/
int				check_syntax_errors(t_token **head);
/*--------------lexer-utils-five--------------*/
int				is_word_sq_dq(char c);
int				token_is_command(t_token *head);
int				is_q_terminated(char *str, int start, int end);
int				tokenize_command(char *input, t_token **head, t_h_token	*var);
/*----------------lexer-utils-six---------------------*/
void			token_h_sep(char *input, t_token **head, t_h_token *var);
int				token_h_quote(char *input, t_token **head, t_h_token *var);
void			token_h_word(char *input, t_token **head, t_h_token *var);
void			token_h_variable(char *input, t_token **head, t_h_token *var);
void			token_h_isspace(char *input, t_token **head, t_h_token *var);
/*---------------lexer-utils-seven--------------------*/
void			token_ready_for_parsing(int l, t_token **src,
					t_token **dest, char **envp);
void			token_preexp_and_update_input(char **input, t_token *dest);
/*---------------lexer-utils-eight--------------------*/
void			token_to_token_preexp(t_token *src, t_token **dest);
void			token_preexp_free(t_token **dest);
void			token_preexp_to_trimed(t_token **dest);
void			token_preexp_to_token_exp(int l, t_token **dest, char **envp);
/*----------------parser----------------------*/
t_pipe_group	*parse_pipeline(t_rdr_const rdr, t_token **tokens);
int				p_command_h_one(t_token *tokens);
void			update_group_list(t_pipe_group **head,
					t_pipe_group **current, t_pipe_group *group,
					t_token **tokens);
/*--------------parser-utils-one-------------*/
int				p_redir_h_one(t_token *tokens);
void			p_redir_h_two(t_rdr_const rdr, t_token_type type,
					t_pipe_group **group, char *file);
void			parse_redir(t_rdr_const rdr, t_token **tokens,
					t_pipe_group *group);
/*---------------parser-utils-two-------------*/
void			p_args_skip_spaces(t_token **temp);
void			join_command_str(t_token **temp, char **current_str);
void			add_arg_and_skip_spaces(char ***args, char *current_str,
					t_token **temp, int *i);
void			parse_command(t_token **tokens, t_pipe_group	*group);
void			parse_args(t_token **tokens, t_pipe_group *group);
/*--------------parser-utils-three------------*/
bool			handle_heredoc(int l, char *end,
					char **heredoc_strs, char **envp);
void			create_file(char *file, int mode);
void			reset_heredoc_fields(t_pipe_group *cmd);
void			print_array(char **str);
/*--------------parser-utils-four-------------*/
void			pipe_group_print(t_pipe_group *group);
t_pipe_group	*pipe_group_init(void);
void			pipe_group_add(t_pipe_group **head, t_pipe_group *new_group);
/*--------------parser-utils-five-------------*/
void			parse_command(t_token **tokens, t_pipe_group	*group);
void			parse_args(t_token **tokens, t_pipe_group *group);
char			**args_join(char **src, char *new_arg);
/*--------------parser-utils-heredoc----------*/
void			expand_heredoc_strs(char **str, int l, char **envp);
void			save_heredoc_str(char *str, char **heredoc_strs);
void			copy_stdin_fd(int *stdin_copy);
void			restore_stdin_fd(int stdin_copy, char **heredoc_strs);
void			pipe_group_free(t_pipe_group **head);
/*---------------expander---------------------*/
char			*expand_var(int l, char *input, char **envp);
void			expand_parsed_commands(int l, t_pipe_group *group, char **envp);
char			*expand_unquoted(int l, char *input, char **envp);
/*---------------expander-utils-one-----------*/
char			*expand_double_quoted(int l, char *input, char **envp);
/*--------------Unix-Signals------------------*/
void			handle_sigint_shell(int signal);
void			handle_sigint_heredoc(int signal);
/*-------------terminal_attributes------------*/
void			change_terminal_echo_ctl(bool turn_off);
/*====================||====GET_NEXT_LINE======||=================*/
//===========================================================//
//==================BUFFER-SIZE=============================//
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif
//=============GET NEXT LINE FUNCTIONS======================//
char			*get_next_line(int fd);
char			*ft_substr_get(char *s, int start, int length);
char			*ft_strjoin_get(char *s1, char *s2, int len);
int				ft_linelen(char *str);
int				ft_str_bs(char *str, char c);
int				ft_strlen_get(const char *str);
char			*get_res(int fd, char *rem);
//===========================================================//
/*====================||====GET_NEXT_LINE======||=================*/
#endif