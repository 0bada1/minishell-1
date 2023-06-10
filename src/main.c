/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:15 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 22:06:54 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

void	excute_simple_cmd(t_shell_s *shell)
{
	if (!shell->command_block[0]->command)
		excute_only_redir(shell->command_block[0]);
	else if (init_redir(shell->command_block[0]) == -1)
	{
		g_exit_code = EXIT_FAILURE;
		return ;
	}
	if (shell->command_block[0]->command)
		g_exit_code = builtin_exec(shell->command_block[0], shell);
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
}

/*
it have 2 roles, 
1- it check if forking required and if not it will excute the builtin by 
	make the redirection
	excute the builtin
	return any redir to original
2- it will loop and fork the proccess in each loop to execute the child
*/
void	start_exec(t_shell_s *shell)
{
	shell->heredoc_flag = 0;
	if (exec_child_heredoc(shell) == -1)
		return ;
	if (forking_required(shell))
		excute_simple_cmd(shell);
	else
	{
		pid_pipes_init(shell);
		if (shell->heredoc_flag != 1)
		{
			close(shell->std_out);
			close(shell->std_in);
			while (++shell->cmd_used < shell->num_commands)
				excute_child(shell, shell->cmd_used);
			parent_after_fork(shell);
		}
		shell->heredoc_flag = 0;
	}
}

/*
chech if it reads spaces by all types
*/
int	check_cmd(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] > 32)
			return (0);
	return (1);
}

/*
this the core function that have infinit loop the keep read the input and 
then do parsing and if no errors it will start excution
*/
void	shell_loop(char **envp, t_shell_s *shell, int i)
{
	char		*cmd;

	while (1)
	{
		cmd = readline("Minishell$ ");
		if (!cmd)
		{
			printf("exit\n");
			break ;
		}
		if (check_cmd(cmd))
			continue ;
		add_history(cmd);
		shell = parse(shell, cmd, envp, ++i);
		export_init(shell, i);
		free(cmd);
		cmd = NULL;
		if (shell && shell->command_block)
		{
			start_exec(shell);
			free_after_execution(shell);
			minishell_reset(shell);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_s	*shell;
	int			i;

	i = -1;
	(void)argc;
	(void)argv;
	(void)envp;
	shell = ft_calloc(sizeof(t_shell_s), 1);
	minishell_init(shell);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(envp, shell, i);
	close_all_fd();
	free_everything(shell);
	return (g_exit_code);
}
