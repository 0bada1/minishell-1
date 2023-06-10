/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:30:45 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/06 18:52:44 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	path_env_check(t_execute *cmd, char **path)
{
	if (!*path && (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~\0", 2)))
		return (ft_putstr_fd("minishell: cd: HOME not set\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if (!*path && !ft_strncmp(cmd->args[1], "-", 2))
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if (!*path && cmd->args[1])
	{
		*path = cmd->args[1];
		return (EXIT_SUCCESS);
	}
	return (0);
}
