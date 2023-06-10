/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:21:15 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 10:47:27 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_flag(int *flag, char *str)
{
	int	i;

	i = -1;
	*flag = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '=')
		{
			*flag = i;
			break ;
		}
	}
}

void	add_only_key(t_env_s *env, char *str)
{
	char	**temp_key_ex;
	char	**temp_value_ex;
	int		i;

	i = -1;
	temp_key_ex = ft_calloc(ft_strstrlen(env->export_key) + 2, sizeof(char *));
	temp_value_ex = ft_calloc(ft_strstrlen(env->export_value) + 2,
			sizeof(char *));
	while (env->export_key && env->export_key[++i])
		temp_key_ex[i] = ft_strdup(env->export_key[i]);
	temp_key_ex[i] = ft_strdup(str);
	i = -1;
	while (env->export_value && env->export_value[++i])
		temp_value_ex[i] = ft_strdup(env->export_value[i]);
	temp_value_ex[i] = ft_strdup(" ");
	free_2d(env->export_key);
	free_2d(env->export_value);
	env->export_key = temp_key_ex;
	env->export_value = temp_value_ex;
}

void	add_args_export(t_env_s *env, int *flag, char *str)
{
	char	**temp_key_ex;
	char	**temp_value_ex;
	int		i;

	i = -1;
	temp_key_ex = ft_calloc(ft_strstrlen(env->export_key) + 2, sizeof(char *));
	temp_value_ex = ft_calloc(ft_strstrlen(env->export_value) + 2,
			sizeof(char *));
	while (env->export_key && env->export_key[++i])
		temp_key_ex[i] = ft_strdup(env->export_key[i]);
	temp_key_ex[i] = ft_calloc(*flag + 1, sizeof(char));
	ft_strlcpy(temp_key_ex[i], str, *flag + 1);
	i = -1;
	while (env->export_value && env->export_value[++i])
		temp_value_ex[i] = ft_strdup(env->export_value[i]);
	temp_value_ex[i] = ft_strdup(str + *flag + 1);
	free_2d(env->export_key);
	free_2d(env->export_value);
	env->export_key = temp_key_ex;
	env->export_value = temp_value_ex;
}

void	add_args_env(t_env_s *env, int *flag, char *str)
{
	char	**temp_envp;
	char	**temp_key;
	int		i;

	i = -1;
	temp_envp = ft_calloc(ft_strstrlen(env->envp) + 2, sizeof(char *));
	temp_key = ft_calloc(ft_strstrlen(env->key) + 2, sizeof(char *));
	while (env->envp && env->envp[++i])
	{
		temp_envp[i] = ft_strdup(env->envp[i]);
		temp_key[i] = ft_strdup(env->key[i]);
	}
	temp_envp[i] = ft_strdup(str);
	temp_key[i] = ft_calloc(*flag + 1, sizeof(char));
	ft_strlcpy(temp_key[i], str, *flag + 1);
	free_2d(env->envp);
	free_2d(env->key);
	env->envp = temp_envp;
	env->key = temp_key;
}

void	add_export_args(char *str, int *flag, t_env_s *env)
{
	int		i;

	i = -1;
	get_flag(flag, str);
	while (env->export_key && env->export_key[++i])
		if (!ft_strncmp(str, env->export_key[i], ft_strlen(str) + 1))
			return ;
	if (*flag != 0)
	{
		add_args_env(env, flag, str);
		add_args_export(env, flag, str);
	}
	else
		add_only_key(env, str);
}
