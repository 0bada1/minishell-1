/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:12:21 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/06 22:52:01 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
this function used to compute the lenth of char ** variable 
it is used to count the number of each redir in the char **names
*/
int	ft_strstrlen(char **str)
{
	int	i;

	if (!str || !str[0])
		return (1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	minishell_reset(t_shell_s *shell)
{
	shell->pipes_fd = 0;
	shell->pid = 0;
	shell->flags = 0;
	shell->commands = 0;
	shell->cmd_line = 0;
	shell->lexer = 0;
	shell->files = 0;
	shell->command_block = 0;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
}

void	minishell_init(t_shell_s *shell)
{
	shell->pipes_fd = 0;
	shell->pid = 0;
	shell->flags = 0;
	shell->commands = 0;
	shell->path = 0;
	shell->cmd_line = 0;
	shell->envp = 0;
	shell->lexer = 0;
	shell->files = 0;
	shell->command_block = 0;
}

void	close_all_fd(void)
{
	int	i;

	i = -1;
	while (++i <= 1024)
		close(i);
}

void	free_error(t_shell_s *shell)
{
	close_all_fd();
	clear_history();
	free_everything(shell);
}
