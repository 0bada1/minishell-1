/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:51:04 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 08:16:34 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_if_dir(char *cmd, t_shell_s *shell, int from)
{
	DIR	*dir;

	if (from == 0)
		return ;
	if (cmd[0] != '.' && cmd[0] != '/')
		return ;
	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free_error(shell);
		exit(126);
	}
}

/*
F_OK: This constant is used to check if the file or directory exists.
X_OK: This constant is used to check if the file or directory is executable.
*/
int	path_check(char *cmd, t_shell_s *shell, int from)
{
	check_if_dir(cmd, shell, from);
	if (cmd[0] != '.' && cmd[0] != '/')
		return (0);
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (1);
		else
		{
			perror("Error");
			return (-1);
		}
	}
	else if (from == 1)
	{
		perror("Error");
		return (2);
	}
	return (0);
}

void	return_child_notfound(t_shell_s *shell, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_error(shell);
	exit(127);
}

void	excute_child_with_path2(t_shell_s *shell, int path_return)
{
	free_error(shell);
	if (path_return == -1)
		exit(126);
	if (path_return == 2)
		exit(127);
}

void	excute_child_with_path(t_shell_s *shell, int cmd_num)
{
	int		i;
	char	*cmd_with_path;
	int		path_return;

	if (!shell->path)
		return_child_notfound(shell, shell->command_block[cmd_num]->command);
	i = -1;
	while (shell->path[++i])
	{
		cmd_with_path = ft_strjoin(shell->path[i],
				shell->command_block[cmd_num]->command);
		path_return = path_check(cmd_with_path, shell, 0);
		if (path_return == 1)
			execve(cmd_with_path, shell->command_block[cmd_num]->args,
				shell->envp->envp);
		else if (path_return == -1 || path_return == 2)
			excute_child_with_path2(shell, path_return);
		free(cmd_with_path);
	}
	return_child_notfound(shell, shell->command_block[cmd_num]->command);
}
