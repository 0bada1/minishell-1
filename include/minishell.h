/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:47:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 17:38:11 by ooutabac         ###   ########.fr       */
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

/* T_COUNTER
- This struct is just for general use to save lines.
It is used so I can easily pass multiple counters between functions and declare
many counters using one variable.
*/
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

/* T_LEXER
- This is where tokenization take place. I sepearate everything into tokens
* What is a token?
- A token is any word seperated by space with a few exceptions.
These exceptions include double and single quotes. If a word is joined with
double quotes, the word outside the quotes and the everything within the
quotes will be in the same token regardless of spaces within the quotes.
If two quotes are joined together, they will also be in the same token
regardless of space.
* Will I need this struct?
- I assume not, you'll mostly be using the t_shell_s as it contains everything
parsed and ready to use. If anything you need to check, you have the tokens
if you had to use it for anything.
*/
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
	// struct	s_env_s	*next; // Next environment variable as a linked list

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
	/*	'>' = infile
		'<' = outfile
		'a' = Append which is ">>"
		'h' = Heredoc which is "<<"
	*/

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
// This is the executor's struct. It is stored as a double pointer
// struct in t_shell, each pointer representing a command block

typedef struct s_shell_s
{
	int			num_commands;
	int			num_pipes;
	int			*pipes_fd;
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

/*------------------------------------KHALED----------------------------------*/
/*-------------------------------------MAIN-----------------------------------*/
int			shell_loop(char **envp);
void		excute_child(t_shell_s *shell, int cmd_num);
/*------------------------------------pipes-----------------------------------*/
void		pid_pipes_init(t_shell_s *shell);
void		pipes_in_child(t_shell_s *shell, int cmd_num);
void		free_error(t_shell_s *shell);
void		close_all_fd(void);
/*------------------------------------redir-----------------------------------*/
int			ft_strstrlen(char **str);
int			init_redir(t_execute *cmd, t_shell_s *shell);
int			init_heredoc(t_execute *cmd, t_shell_s *shell);
void		open_exec_heredoc(t_files *files, t_shell_s *shell);
int			open_outfile(t_files *files, int i);
int			open_appendfile(t_files *files, int i);
int			open_infile(t_files *files, int i);
/*-----------------------------------signal----------------------------------*/
void		ft_ctrl_c(int sig);
/*-----------------------------------builtin---------------------------------*/
int			is_builtin(char *cmd);
int			builtin_exec(t_execute *exec, t_shell_s *shell);
int			ft_echo(char **args);
int			ft_env(char **arg, t_env_s *env);
int			ft_pwd(void);
int			ft_unset(t_execute *exec);
int			ft_export(t_execute *cmd);
int			ft_cd(t_execute *cmd);
void		ft_exit(t_execute *exec, t_shell_s *shell);

/*----------------------------------OBADA-----------------------------------*/
/*---------------------------------PARSING----------------------------------*/
t_shell_s	*parse(t_shell_s *minishell, char *str, char **envp, int iteration);

/*-----------------------------------SKIP-----------------------------------*/
int			skip_spaces(char *str, int i);
int			skip_token(char *str, int i);
int			skip_symbols(char *str, int i);
int			skip_squotes(char *str, int i);
int			skip_dquotes(char *str, int i);

/*----------------------------COUNT_REDIRECTIONS----------------------------*/
int			count_infiles(char	**str);
int			count_outfiles(char	**str);
int			count_appends(char	**str);
int			count_heredocs(char	**str);

/*----------------------------------UTSIL1----------------------------------*/
int			ft_strlen_spaces(char *str, int i);
int			ft_strlen_equals(char *str);
int			count_tokens(char *str);
int			count_pipes(char *str);

/*----------------------------------UTSIL2----------------------------------*/
t_shell_s	*get_path(t_shell_s	*minishell, char **envp);
t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[]);
t_shell_s	*get_flags(t_shell_s *minishell);
t_shell_s	*get_commands(t_shell_s *minishell);
t_shell_s	*get_num_commands(t_shell_s *minishell);
t_shell_s	*get_execution_blocks(t_shell_s *minishell);
t_execute	*get_files(t_shell_s *minishell, t_execute *execute_block,
				char **command_block, char **raw_command_block);

/*----------------------------------UTSIL3----------------------------------*/
t_shell_s	*lexer(t_shell_s *minishell, char *str);
int			number_of_dquotes(char *str);
int			number_of_squotes(char *str);
t_shell_s	*malloc_lexer(t_shell_s *minishell, char *str);
void		lexer_double_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
void		lexer_single_symbol(t_shell_s *minishell,
				t_counter *c, char *str);
char		**skip_double_quote_and_assign(
				t_counter *count, char *str, char **blocks);
char		**skip_single_quote_and_assign(
				t_counter *count, char *str, char **blocks);

/*----------------------------------UTSIL4----------------------------------*/
int			num_of_tokens(char *str);
int			token_size(char *str, int i);
int			is_heredoc_append(char *str, t_counter *c);
int			is_infile_outfile_pipe(char *str, t_counter *c);

/*----------------------------------UTSIL5----------------------------------*/
int			check_if_command(t_shell_s *minishell, char *token, int token_num);
int			get_num_flags(char **token, int i);
int			check_validity(t_shell_s *minishell, char *str);

/*----------------------------------UTSIL6----------------------------------*/
t_shell_s	*raw_lexer(t_shell_s *minishell, char *str);
int			raw_token_size(char *str, int i);
char		**split_pipes(char	*str);
char		**split_command_block(t_shell_s *minishell, int token_num);
char		**split_raw_command_block(t_shell_s *minishell, int token_num);
int			num_of_tokens_to_pipe(char **tokens, int token_num);
int			length_to_pipe(char *str, int i);

/*--------------------------------DOLLAR_SIGN1------------------------------*/
char		*dollar_sign(t_shell_s *minishell, char *cmd_line);

/*------------------------------------FREE----------------------------------*/
void		free_everything(t_shell_s *minishell);
void		free_after_execution(t_shell_s *minishell);
void		free_and_null(void *ptr);
void		free_2d(char **array);
void		free_3d(char ***array);

#endif