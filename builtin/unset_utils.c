/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:31:46 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/06 18:37:34 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_args_check(char *str)
{
	int		i;
	char	r[19];

	ft_strlcpy(r, " !@$%^-\\+{}*#~.=;", 19);
	i = -1;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[++i] != '\0')
	{
		if (ft_strchr(r, str[i]) != NULL)
			return (0);
		else if (!str[i + 1])
			return (1);
	}
	return (0);
}

/*
used the remove the env from all arrays in t_env_s stract
*/
void	remove_env_from_list(t_env_s *env, int position)
{
	env->env_size--;
	free(env->envp[position]);
	free(env->key[position]);
	while (env->envp[position] && env->key[position])
	{
		env->envp[position] = env->envp[position + 1];
		env->key[position] = env->key[position + 1];
		position++;
	}
	env->envp[position] = 0;
	env->key[position] = 0;
}

void	remove_export_from_list(t_env_s *env, int position)
{
	free(env->export_key[position]);
	free(env->export_value[position]);
	while (env->export_key[position])
	{
		env->export_key[position] = env->export_key[position + 1];
		env->export_value[position] = env->export_value[position + 1];
		position++;
	}
	env->export_key[position] = 0;
	env->export_value[position] = 0;
}

/*
used to locate the env_key position in the array
*/
int	unset_arg_comp(char *arg, char **env_key)
{
	int	i;

	i = -1;
	while (env_key[++i])
	{
		if (!ft_strncmp(arg, env_key[i], ft_strlen(arg) + 1))
			return (i);
	}
	return (-1);
}

int	export_arg_comp(char *arg, char **env_key)
{
	int	i;

	i = -1;
	while (env_key[++i])
	{
		if (!ft_strncmp(arg, env_key[i], ft_strlen(arg) + 1))
			return (i);
	}
	return (-1);
}
