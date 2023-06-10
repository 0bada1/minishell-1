/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:22:08 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 10:47:46 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_key_value(char **key, char **value, int i)
{
	char	*temp;
	char	*temp2;

	temp = key[i];
	temp2 = value[i];
	key[i] = key[i + 1];
	value[i] = value[i + 1];
	key[i + 1] = temp;
	value[i + 1] = temp2;
}

void	sort_key_value(char **key, char **value)
{
	int		i;
	int		len;
	int		j;

	j = -1;
	len = ft_strstrlen(key);
	while (++j < len)
	{
		i = -1;
		while (key && key[++i])
		{
			if (key[i + 1] && ft_strncmp(key[i], key[i + 1],
					ft_strlen(key[i]) + 1) > 0)
				swap_key_value(key, value, i);
		}
	}
}

void	env_export_printing_value(t_env_s *env, int i)
{
	int		j;
	char	spesial[3];

	ft_strlcpy(spesial, "$\"", 3);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	j = -1;
	while (env->export_value[i][++j])
	{
		if (ft_strchr(spesial, env->export_value[i][j]))
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(env->export_value[i][j], STDOUT_FILENO);
	}
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	env_export_printing(t_env_s *env)
{
	int	i;

	sort_key_value(env->export_key, env->export_value);
	i = -1;
	while (env->export_key && env->export_key[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->export_key[i], STDOUT_FILENO);
		if (env->export_value[i] && ft_strncmp(env->export_value[i],
				" ", 2) != 0)
			env_export_printing_value(env, i);
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

/*
1 -> do nothing
0 -> not valid
2 -> ok to add
*/

int	export_args_check(char *str)
{
	int		i;
	char	r[17];
	int		flag;

	ft_strlcpy(r, " !@$%^-\\+{}*#~.", 17);
	i = -1;
	flag = 0;
	if (!ft_strncmp(str, "_\0", 2))
		return (1);
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[++i] != '\0')
	{
		if (str[i] == '=')
			flag = i;
		else if (flag == 0 && ft_strchr(r, str[i]) != NULL)
			return (0);
		if (!str[i + 1])
			return (1);
	}
	return (0);
}
