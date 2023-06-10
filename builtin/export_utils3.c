/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:22:36 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 19:05:57 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_in_env(t_env_s *env, char *str, int *flag)
{
	int		i;
	char	*key;

	get_flag(flag, str);
	if (*flag != 0)
	{
		key = ft_calloc(*flag + 1, sizeof(char));
		ft_strlcpy(key, str, *flag + 1);
		i = -1;
		while (env->key && env->key[++i])
		{
			if (!ft_strncmp(key, env->key[i], ft_strlen(key) + 1))
			{
				free(key);
				return (i);
			}
		}
		free(key);
		return (-1);
	}
	return (-1);
}

void	add_value_to_env(int p, t_env_s *env, char *str, int *flag)
{
	(void)flag;
	free(env->envp[p]);
	env->envp[p] = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_strlcpy(env->envp[p], str, ft_strlen(str) + 1);
}

void	add_value_to_export(int p, t_env_s *env, char *str, int *flag)
{
	free(env->export_value[p]);
	env->export_value[p] = 0;
	env->export_value[p] = ft_calloc(ft_strlen(str) - *flag + 1, sizeof(char));
	ft_strlcpy(env->export_value[p], str + *flag + 1, ft_strlen(str) - *flag);
}

void	ft_export2(t_execute *cmd, int *flag, int p, int i)
{
	if (p != -1)
	{
		add_value_to_export(p, cmd->env, cmd->args[i], flag);
		p = check_in_env(cmd->env, cmd->args[i], flag);
		if (p != -1)
			add_value_to_env(p, cmd->env, cmd->args[i], flag);
		else if (p == -1 && flag != 0)
			add_args_env(cmd->env, flag, cmd->args[i]);
	}
	else
		add_export_args(cmd->args[i], flag, cmd->env);
}

void	exit_export(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
