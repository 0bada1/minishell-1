/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:47:48 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/06 18:03:20 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(t_execute *exec)
{
	int		i;
	int		position;

	i = 0;
	while (exec->args[++i])
	{
		if (unset_args_check(exec->args[i]) == 0)
		{
			ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
			ft_putstr_fd(exec->args[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (!exec->env->envp || !exec->env->envp[0])
			return (EXIT_SUCCESS);
		position = unset_arg_comp(exec->args[i], exec->env->key);
		if (position != -1)
			remove_env_from_list(exec->env, position);
		position = export_arg_comp(exec->args[i], exec->env->export_key);
		if (position != -1)
			remove_export_from_list(exec->env, position);
	}
	return (EXIT_SUCCESS);
}
