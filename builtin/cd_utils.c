/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:24:12 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 09:58:40 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_pwd_p_env(t_env_s *env)
{
	int		i;
	int		old_pwd_p;

	old_pwd_p = -1;
	i = -1;
	while (env->envp && env->envp[0] && env->key[++i])
		if (!ft_strncmp(env->key[i], "OLDPWD", 7))
			old_pwd_p = i;
	return (old_pwd_p);
}

int	get_pwd_p_export(t_env_s *env)
{
	int		i;
	int		old_pwd_p_export;

	i = -1;
	old_pwd_p_export = -1;
	while (env->envp && env->envp[0] && env->export_key[++i])
		if (!ft_strncmp(env->export_key[i], "OLDPWD", 7))
			old_pwd_p_export = i;
	return (old_pwd_p_export);
}

void	add_to_env(t_env_s *env, char *pwd, char *old_pwd)
{
	int		i;
	int		old_pwd_p;

	old_pwd_p = get_pwd_p_env(env);
	i = -1;
	if (old_pwd_p != -1)
	{
		free(env->envp[old_pwd_p]);
		env->envp[old_pwd_p] = ft_strjoin("OLDPWD=", old_pwd);
	}
	while (env->envp && env->envp[0] && env->key[++i])
	{
		if (!ft_strncmp(env->key[i], "PWD", 4))
		{
			if (env->envp && env->envp[i])
				free(env->envp[i]);
			env->envp[i] = pwd;
		}
		else if (i == ft_strstrlen(env->key))
			free (pwd);
	}
}

void	add_to_export(t_env_s *env, char *pwd_export, char *old_pwd)
{
	int		i;
	int		old_pwd_p;

	old_pwd_p = get_pwd_p_export(env);
	if (old_pwd_p != -1)
	{
		free(env->export_value[old_pwd_p]);
		env->export_value[old_pwd_p] = old_pwd;
	}
	else
		free (old_pwd);
	i = -1;
	while (env->envp && env->envp[0] && env->export_key[++i])
	{
		if (!ft_strncmp(env->export_key[i], "PWD", 4))
		{
			if (env->export_value && env->export_value[i])
				free(env->export_value[i]);
			env->export_value[i] = pwd_export;
		}
		else if (i == ft_strstrlen(env->export_key))
			free (pwd_export);
	}
}
