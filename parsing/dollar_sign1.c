/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:23:15 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:58:50 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

int	length_of_dollar_sign(char *str)
{
	t_counter	count;

	if (!str || !str[0] || str[0] != '$')
		return (0);
	count.i = 1;
	while (str[count.i] && (ft_isalnum(str[count.i]) == 1
			|| str[count.i] == '_'))
		count.i++;
	return (count.i - 1);
}

int	get_length_of_env(char *str)
{
	t_counter	count;
	char		*env_value;
	char		*env_key;

	if (!str || !str[0] || str[0] != '$' || !str[1])
		return (0);
	count.i = 1;
	count.j = length_of_dollar_sign(str);
	env_key = malloc(sizeof(char) * count.j);
	while (str[count.i] && (ft_isalnum(str[count.i]) != 0
			|| str[count.i] == '_'))
	{
		env_key[count.i - 1] = str[count.i];
		count.i++;
	}
	env_key[count.i - 1] = '\0';
	env_value = getenv(env_key + 1);
	count.counter = ft_strlen(env_value);
	if (env_key)
		free(env_key);
	if (env_value)
		free(env_value);
	return (count.counter);
}

int	is_expandable_condition(char *str, t_counter *count)
{
	if (str[count->i] == '$' && str[count->i + 1]
		&& (ft_isalnum(str[count->i + 1]) == 1
			|| str[count->i + 1] == '_'))
		return (TRUE);
	count->i++;
	return (FALSE);
}
