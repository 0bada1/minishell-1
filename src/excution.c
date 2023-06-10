/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:07:28 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 17:58:17 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

int	parent_waitpid(t_shell_s *shell)
{
	int	i;
	int	status;
	int	exit_code;

	i = -1;
	exit_code = -1;
	while (++i < shell->num_commands)
	{
		if (waitpid(shell->pid[i], &status, 0) == -1)
		{
			ft_putstr_fd("Waitpid failed\n", STDERR_FILENO);
			free_error(shell);
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

void	parent_after_fork(t_shell_s *shell)
{
	int	i;
	int	exit_code;

	i = 0;
	if (shell->num_pipes > 0)
		while (i < shell->num_pipes * 2)
			close(shell->pipes_fd[i++]);
	exit_code = parent_waitpid(shell);
	if (exit_code != -1)
		g_exit_code = exit_code;
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	close(shell->std_out);
	close(shell->std_in);
}

int	exec_child_heredoc(t_shell_s *shell)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (++i < shell->num_commands)
		if (shell->command_block[i]->files->limiter[0] != NULL)
			break ;
	i = -1;
	while (++i < shell->num_commands)
	{
		if (shell->command_block[i]->files->limiter[0] != NULL)
			r = open_exec_heredoc(shell->command_block[i]->files, shell);
		if (r == -1)
			return (-1);
	}
	return (0);
}

/*
check if forking required in order to call fork or excute by parent
*/
int	forking_required(t_shell_s *shell)
{
	if (shell->num_pipes == 0)
	{
		if (!shell->command_block[0]->command)
			return (1);
		if (is_builtin(shell->command_block[0]->command))
			return (1);
	}
	return (0);
}

void	excute_only_redir(t_execute *cmd)
{
	if (init_redir(cmd) == -1)
	{
		g_exit_code = EXIT_FAILURE;
		return ;
	}
	g_exit_code = EXIT_SUCCESS;
}
