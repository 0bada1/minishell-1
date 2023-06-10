/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:15:09 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 18:29:02 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_pwd_env(t_env_s *env, char *old_pwd)
{
	char	*pwd;
	char	*get_cwd;
	char	*pwd_export;

	get_cwd = getcwd(NULL, 0);
	if (!get_cwd)
		return ;
	pwd = ft_strjoin("PWD=", get_cwd);
	free (get_cwd);
	pwd_export = ft_strdup(pwd + 4);
	add_to_env(env, pwd, old_pwd);
	add_to_export(env, pwd_export, old_pwd);
}

char	*get_home_path(t_execute *cmd)
{
	int		i;
	char	*path;

	path = 0;
	i = -1;
	while (cmd->env->key[++i])
	{
		if (!ft_strncmp(cmd->env->key[i], "HOME", 5))
		{
			path = cmd->env->envp[i] + 5;
			break ;
		}
	}
	return (path);
}

char	*get_old_pwd(t_execute *cmd)
{
	int		i;
	char	*path;

	path = 0;
	i = -1;
	while (cmd->env->key[++i])
	{
		if (!ft_strncmp(cmd->env->key[i], "OLDPWD", 7))
		{
			path = cmd->env->envp[i] + 7;
			break ;
		}
	}
	return (path);
}

int	action_cd(t_execute *cmd, char *path)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (EXIT_FAILURE);
	if (!chdir(path))
		add_pwd_env(cmd->env, old_pwd);
	else
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		perror(" ");
		return (1);
	}
	return (0);
}

int	ft_cd(t_execute *cmd)
{
	char	*path;

	path = 0;
	if (ft_strstrlen(cmd->args) > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), EXIT_FAILURE);
	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~\0", 2))
	{
		if (!cmd->env->envp && !cmd->env->envp[0])
			return (ft_putstr_fd("minishell: cd: HOME not set\n",
					STDERR_FILENO), EXIT_FAILURE);
		path = get_home_path(cmd);
	}
	else if (!ft_strncmp(cmd->args[1], "-", 2))
	{
		if (!cmd->env->envp && !cmd->env->envp[0])
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n",
					STDERR_FILENO), EXIT_FAILURE);
		path = get_old_pwd(cmd);
	}
	if (path_env_check(cmd, &path))
		return (EXIT_FAILURE);
	return (action_cd(cmd, path));
}
