/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:03:04 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 10:38:43 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	return (0);
}

int	builtin_exec(t_execute *exec, t_shell_s *shell)
{
	if (!ft_strncmp(exec->command, "export", 7))
		return (ft_export(exec));
	else if (!ft_strncmp(exec->command, "cd", 3))
		return (ft_cd(exec));
	if (!ft_strncmp(exec->command, "echo", 5))
		return (ft_echo(exec->args));
	else if (!ft_strncmp(exec->command, "env", 4))
		return (ft_env(exec->args, exec->env));
	else if (!ft_strncmp(exec->command, "unset", 6))
		return (ft_unset(exec));
	else if (!ft_strncmp(exec->command, "exit", 5))
		ft_exit(exec, shell);
	else if (!ft_strncmp(exec->command, "pwd", 4))
		return (ft_pwd());
	return (0);
}
