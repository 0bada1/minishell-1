/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 21:17:04 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>

# define TRUE 0
# define FALSE 1
# define STD_IN 0
# define STD_OUT 1
# define STD_ERROR 2

typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	n;
	int	x;
	int	y;
	int	z;
	int	trigger;
	int	trigger2;
	int	counter;
	int	length;
}t_counter;

typedef struct s_lexer
{
	char	**command_blocks;
	char	**raw_tokens;
	char	**tokens;
	int		num_of_tokens;
	int		num_of_pipes;
	int		num_of_commands;
}t_lexer;

typedef struct s_env_s
{
	int				env_size;
	char			**export_env;
	char			**export_key;
	char			**export_value;
	char			**envp;
	char			**key;
	char			**value;
}t_env_s;

typedef struct s_files
{
	int		num_of_redirections;
	int		infile_fd;
	int		outfile_fd;
	int		append_fd;
	int		heredoc_fd;
	char	**infile_name;
	char	**outfile_name;
	char	**append_name;
	char	**limiter;
	char	*redirect_type;
}t_files;

typedef struct s_execute
{
	int		num_commands;
	int		num_pipes;
	char	*command;
	char	**args;
	char	**tokens;
	t_files	*files;
	t_env_s	*env;
}t_execute;

typedef struct s_shell_s
{
	int			num_commands;
	int			num_pipes;
	int			*pipes_fd;
	int			heredoc_flag;
	pid_t		*pid;
	int			cmd_used;
	int			exit_code;
	char		***flags;
	char		**commands;
	char		**path;
	char		*cmd_line;
	int			std_in;
	int			std_out;
	t_env_s		*envp;
	t_lexer		*lexer;
	t_files		*files;
	t_execute	**command_block;
}t_shell_s;

/*--------------------------------KHALED-------------------------------*/
/*---------------------------------MAIN--------------------------------*/
void		shell_loop(char **envp, t_shell_s *shell, int i);
void		excute_simple_cmd(t_shell_s *shell);
void		excute_only_redir(t_execute *cmd);
int			forking_required(t_shell_s *shell);
int			exec_child_heredoc(t_shell_s *shell);
void		parent_after_fork(t_shell_s *shell);
void		update_path(t_shell_s *shell);
void		check_if_dir(char *cmd, t_shell_s *shell, int from);
int			path_check(char *cmd, t_shell_s *shell, int from);
void		return_child_notfound(t_shell_s *shell, char *str);
void		excute_child_with_path(t_shell_s *shell, int cmd_num);
void		excute_child_non_builtin(t_shell_s *shell, int cmd_num);
void		excute_child2(t_shell_s *shell, int cmd_num);
void		excute_child(t_shell_s *shell, int cmd_num);
void		minishell_reset(t_shell_s *shell);
void		minishell_init(t_shell_s *shell);
/*---------------------------------pipes--------------------------------*/
void		pid_pipes_init(t_shell_s *shell);
void		pipes_in_child(t_shell_s *shell, int cmd_num);
void		free_error(t_shell_s *shell);
void		close_all_fd(void);
/*---------------------------------redir--------------------------------*/
int			ft_strstrlen(char **str);
int			init_redir(t_execute *cmd);
int			open_exec_heredoc(t_files *files, t_shell_s *shell);
int			open_outfile(t_files *files, int i);
int			open_appendfile(t_files *files, int i);
int			open_infile(t_files *files, int i);
/*--------------------------------signal-------------------------------*/
void		ft_ctrl_c(int sig);
/*--------------------------------builtin-------------------------------*/
int			is_builtin(char *cmd);
int			builtin_exec(t_execute *exec, t_shell_s *shell);
int			ft_echo(char **args);
int			ft_env(char **arg, t_env_s *env);
int			ft_pwd(void);
int			unset_args_check(char *str);
void		remove_env_from_list(t_env_s *env, int position);
void		remove_export_from_list(t_env_s *env, int position);
int			unset_arg_comp(char *arg, char **env_key);
int			export_arg_comp(char *arg, char **env_key);
int			ft_unset(t_execute *exec);
int			get_pwd_p_env(t_env_s *env);
int			get_pwd_p_export(t_env_s *env);
void		add_to_env(t_env_s *env, char *pwd, char *old_pwd);
int			path_env_check(t_execute *cmd, char **path);
int			ft_cd(t_execute *cmd);
void		get_flag(int *flag, char *str);
void		add_only_key(t_env_s *env, char *str);
void		add_args_export(t_env_s *env, int *flag, char *str);
void		add_args_env(t_env_s *env, int *flag, char *str);
void		add_export_args(char *str, int *flag, t_env_s *env);
void		swap_key_value(char **key, char **value, int i);
void		sort_key_value(char **key, char **value);
void		env_export_printing(t_env_s *env);
int			export_args_check(char *str);
int			check_in_export(t_env_s *env, char *str, int *flag);
void		add_to_export(t_env_s *env, char *pwd_export, char *old_pwd);
int			check_in_env(t_env_s *env, char *str, int *flag);
void		add_value_to_env(int p, t_env_s *env, char *str, int *flag);
void		add_value_to_export(int p, t_env_s *env, char *str, int *flag);
void		ft_export2(t_execute *cmd, int *flag, int p, int i);
void		exit_export(char *str);
void		export_init(t_shell_s *shell, int flag);
int			ft_export(t_execute *cmd);
void		ft_exit(t_execute *exec, t_shell_s *shell);

/*----------------------------------OBADA-----------------------------------*/
/*-----------------------------CHECK_VALIDITY1------------------------------*/
int			check_validity_case6(t_shell_s *minishell, t_counter *count);
int			check_validity_case7(t_shell_s *minishell, t_counter *count);
int			check_validity_case8(t_shell_s *minishell, t_counter *count);
int			check_validity_all_cases(t_shell_s *minishell, t_counter *count);
int			check_validity(t_shell_s *minishell, char *str);

/*-----------------------------CHECK_VALIDITY2------------------------------*/
int			check_validity_case1(t_shell_s *minishell, t_counter *count);
int			check_validity_case2(t_shell_s *minishell, t_counter *count);
int			check_validity_case3(t_shell_s *minishell, t_counter *count);
int			check_validity_case4(t_shell_s *minishell, t_counter *count);
int			check_validity_case5(t_shell_s *minishell, t_counter *count);

/*----------------------------COUNT_REDIRECTIONS----------------------------*/
int			count_infiles(char	**str);
int			count_outfiles(char	**str);
int			count_appends(char	**str);
int			count_heredocs(char	**str);
int			count_pipes(char *str);

/*--------------------------------DOLLAR_SIGN1------------------------------*/
int			length_of_dollar_sign(char *str);
int			get_length_of_env(char *str);
int			is_expandable_condition(char *str, t_counter *count);

/*--------------------------------DOLLAR_SIGN2------------------------------*/
t_shell_s	*assign_tokens(t_shell_s *minishell);
void		assign_tokens_dquotes(t_shell_s *minishell, t_counter *count);
void		assign_tokens_squotes(t_shell_s *minishell, t_counter *count);
void		assign_tokens_loop(t_shell_s *minishell, t_counter *count);
char		*dollar_sign(t_shell_s *minishell, char *cmd_line);

/*--------------------------------DOLLAR_SIGN3------------------------------*/
void		expand_env_variables_elseif(t_shell_s *minishell,
				char *old_token, t_counter *count);
t_shell_s	*expand_env_variables(t_shell_s *minishell);
void		token_size2_squotes(char *str, t_counter *count);
void		token_size2_dquotes(char *str, t_counter *count);
int			token_size2(char *str);

/*--------------------------------DOLLAR_SIGN4------------------------------*/
int			exit_expansion_token_size(t_shell_s *minishell, char *str);
char		*expand_exit_code_token_dquote(t_shell_s *minishell,
				char *str, char *new_str, t_counter *count);
char		*expand_exit_code_token_squote(char *str,
				char *new_str, t_counter *count);
char		*expand_exit_code_token_else(char *str,
				char *new_str, char *exit_code, t_counter *count);
char		*expand_exit_code_token(t_shell_s *minishell, char *str);

/*--------------------------------DOLLAR_SIGN5------------------------------*/
void		expand_token_initialize(void *dollar_sign,
				void *new_token, t_counter *count);
char		*expand_token(char *old_token);
void		exit_expansion_token_size_dquote(char *str,
				char *tmp, t_counter *count);
void		exit_expansion_token_size_squote(char *str, t_counter *count);
void		exit_expansion_token_size_else(char *str,
				char *tmp, t_counter *count);

/*--------------------------------DOLLAR_SIGN6------------------------------*/
void		expand_token_counter_zero(t_counter *count);
int			expand_token_condition(char *old_token, t_counter *count);
char		*expand_token_v3(char *new_token,
				char *env_value, char *old_token, t_counter *count);
char		*etlv1(char *new_token, char *env_value, char *old_token,
				t_counter *count);
char		*expand_token_loop(char *neew, char *old_token, char *env_value,
				t_counter *count);

/*--------------------------------DOLLAR_SIGN7------------------------------*/
int			is_exit_code_expansion(char *str);
char		*get_dollar_sign_v1(char *old_token,
				char *dollar_sign, t_counter *count);
char		*get_dollar_sign(char *old_token,
				char *dollar_sign, t_counter *count);
char		*expand_token_v1(char *env_value,
				char *old_token, char *dollar_sign, t_counter *count);
char		*expand_token_v2(char *env_value,
				char *new_token, char *old_token, t_counter *count);

/*--------------------------------DOLLAR_SIGN8------------------------------*/
int			is_expandable_condition2(char *str, t_counter *count);
int			is_expandable(char *str);
int			number_of_expansions(char *str);
int			is_exit_code_expansion_condition(char *str, t_counter *count);
int			is_exit_code_expansion_condition2(char *str, t_counter *count);

/*------------------------------------FREE----------------------------------*/
void		free_everything(t_shell_s *minishell);
void		free_after_execution(t_shell_s *minishell);
void		free_and_null(void *ptr);
void		free_2d(char **array);
void		free_3d(char ***array);

/*------------------------------GET_COMMANDS--------------------------------*/
t_shell_s	*get_commands(t_shell_s *minishell);
t_shell_s	*get_num_commands(t_shell_s *minishell);
int			check_if_command(t_shell_s *minishell, char *token, int token_num);
void		get_commands_v1(t_shell_s *minishell, t_counter *count);

/*---------------------------------GET_FLAGS--------------------------------*/
int			get_num_flags(char **token, int i);
void		get_flags_v3(t_shell_s *minishell, t_counter *count);
void		get_flags_v2(t_shell_s *minishell, t_counter *count);
void		get_flags_v1(t_shell_s *minishell, t_counter *count);
t_shell_s	*get_flags(t_shell_s *minishell);

/*------------------------------GET_ENV_STRUCT------------------------------*/
t_shell_s	*get_path(t_shell_s *minishell, char **envp);
int			ft_strlen_equals(char *str);
t_shell_s	*get_env_struct_v1(t_shell_s *minishell, char *envp[]);
t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[]);

/*------------------------------GET_EXEC_STRUCT-----------------------------*/
t_shell_s	*get_exec_blocks_v2(t_shell_s *minishell, int i, int z);
void		get_exec_blocks_v1(t_shell_s *minishell, t_counter *c,
				char **command_block, char **raw_command_block);
t_shell_s	*get_execution_blocks(t_shell_s *minishell);
int			is_heredoc_append(char *str, t_counter *c);
int			is_infile_outfile_pipe(char *str, t_counter *c);

/*--------------------------------GET_FILES1--------------------------------*/
void		get_files_append_condition(t_execute *execute_block,
				char **command_block, t_counter *count);
void		get_files_heredoc_condition(t_execute *execute_block,
				char **command_block, t_counter *count);
void		get_files_infile_condition(t_execute *execute_block,
				char **command_block, t_counter *count);

/*--------------------------------GET_FILES2--------------------------------*/
void		get_files_outfile_condition(t_execute *execute_block,
				char **command_block, t_counter *count);
void		get_files_malloc_names(t_execute *execute_block,
				char **raw_command_block);
void		get_files_initialize_counters(t_counter *count);
void		get_files_nullify_vars(t_execute *execute_block, t_counter *count);
t_execute	*get_files(t_shell_s *minishell, t_execute *execute_block,
				char **command_block, char **raw_command_block);

/*------------------------------LENGTH_TO_PIPE------------------------------*/
void		length_to_pipe_dquotes(char *str, t_counter *count);
void		length_to_pipe_squotes(char *str, t_counter *count);
int			length_to_pipe(char *str, int i);

/*----------------------------------LEXER1----------------------------------*/
t_shell_s	*malloc_lexer(t_shell_s *minishell, char *str);
void		lexer_dquotes_assign(t_shell_s *minishell, t_counter *c, char *str);
void		lexer_squotes_assign(t_shell_s *minishell, t_counter *c, char *str);
t_shell_s	*lexer(t_shell_s *minishell, char *str);

/*----------------------------------LEXER2----------------------------------*/
void		lexer_double_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
void		lexer_not_space_tab(t_shell_s *minishell, t_counter *c, char *str);
void		lexer_single_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
void		lexer_loop2(t_shell_s *minishell, char *str, t_counter *c);
void		lexer_loop(t_shell_s *minishell, char *str, t_counter *c);

/*--------------------------------NUM_TOKENS--------------------------------*/
void		num_of_tokens_loop(char *str, t_counter *count);
int			num_of_tokens(char *str);

/*---------------------------------PARSING----------------------------------*/
t_shell_s	*parse_cmds(t_shell_s *minishell, char *str);
t_shell_s	*parse_fds(t_shell_s *minishell, int iteration);
t_shell_s	*parse_dsl(t_shell_s *minishell, char *str, int num, char **envp);
t_shell_s	*parse(t_shell_s *minishell, char *str, char **envp, int iteration);

/*--------------------------------RAW_LEXER1--------------------------------*/
t_shell_s	*malloc_raw_lexer(t_shell_s *minishell);
void		raw_lexer_double_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
void		raw_lexer_single_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
void		raw_lexer_loop2(t_shell_s *minishell, char *str, t_counter *c);
void		raw_lexer_loop(t_shell_s *minishell, char *str, t_counter *c);

/*--------------------------------RAW_LEXER2--------------------------------*/
t_shell_s	*raw_lexer(t_shell_s *minishell, char *str);
void		raw_token_size_squote(char *str, t_counter *c);
void		raw_token_size_dquote(char *str, t_counter *c);
void		raw_token_size_trigger(t_counter *c);
int			raw_token_size(char *str, int i);

/*-----------------------------------SKIP1----------------------------------*/
int			skip_spaces(char *str, int i);
int			skip_token(char *str, int i);
int			skip_symbols(char *str, int i);
int			skip_squotes(char *str, int i);
int			skip_dquotes(char *str, int i);

/*-----------------------------------SKIP2----------------------------------*/
char		**skip_double_quote_and_assign(
				t_counter *count, char *str, char **blocks);
char		**skip_single_quote_and_assign(
				t_counter *count, char *str, char **blocks);

/*----------------------------SPLIT_COMMAND_BLOCK---------------------------*/
int			num_of_tokens_to_pipe(char **tokens, int token_num);
char		**split_raw_command_block(t_shell_s *minishell, int token_num);
char		**split_command_block(t_shell_s *minishell, int token_num);
int			number_of_squotes(char *str);
int			number_of_dquotes(char *str);

/*--------------------------------SPLIT_PIPES-------------------------------*/
void		token_size_squote(char *str, t_counter *c);
void		token_size_dquote(char *str, t_counter *c);
void		token_size_trigger(t_counter *c);
int			token_size(char *str, int i);
char		**split_pipes(char	*str);

/*--------------------------------TOKEN_SIZE--------------------------------*/
void		token_size_squote(char *str, t_counter *c);
void		token_size_dquote(char *str, t_counter *c);
void		token_size_trigger(t_counter *c);
int			token_size(char *str, int i);

#endif