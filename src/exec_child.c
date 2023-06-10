/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:18:42 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 08:16:39 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_path(t_shell_s *shell)
{
	free_2d(shell->path);
	get_path(shell, shell->envp->envp);
}

/*
this function excute the non_builtin command, it do the following
1- update the env
2- check if bath provided and excute if yes
3- if no join the path with cmd
	check the validity by access function
	yes -> execve
	no -> error - not found 
*/
void	excute_child_non_builtin(t_shell_s *shell, int cmd_num)
{
	int		r;

	r = path_check(shell->command_block[cmd_num]->command, shell, 1);
	if (r == 1)
	{
		if (execve(shell->command_block[cmd_num]->command,
				shell->command_block[cmd_num]->args, shell->envp->envp) == -1)
		{
			perror("Error");
			free_error(shell);
			exit(126);
		}
	}
	else if (r == -1)
	{
		free_error(shell);
		exit(126);
	}
	else if (r == 2)
	{
		free_error(shell);
		exit(127);
	}
	update_path(shell);
	excute_child_with_path(shell, cmd_num);
}

void	excute_child2(t_shell_s *shell, int cmd_num)
{
	int	status;

	status = 0;
	if (init_redir(shell->command_block[cmd_num]) == -1)
	{
		free_error(shell);
		exit(EXIT_FAILURE);
	}
	if (shell->command_block[cmd_num]->command)
	{
		if (is_builtin(shell->command_block[cmd_num]->command))
		{
			status = builtin_exec(shell->command_block[cmd_num], shell);
			free_error(shell);
			exit(status);
		}
		else
			excute_child_non_builtin(shell, cmd_num);
	}
}

/*
this function will be caled if forking is requied according the test
it will do the following:
1- fork the process
2- handle the pipes in child proces
3- apply the redir 
4- excute builin if it is so
5- call the function that excute the non_builtin 
6- wait for child to finish
*/
void	excute_child(t_shell_s *shell, int cmd_num)
{
	shell->pid[cmd_num] = fork();
	if (shell->pid[cmd_num] == -1)
	{
		ft_putstr_fd("fork failure\n", STDERR_FILENO);
		free_error(shell);
	}
	else if (shell->pid[cmd_num] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipes_in_child(shell, cmd_num);
		excute_child2(shell, cmd_num);
		free_error(shell);
		exit(EXIT_SUCCESS);
	}
}
