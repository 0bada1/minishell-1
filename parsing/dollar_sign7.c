/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:56:03 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:56:11 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_exit_code_expansion(char *str)
{
	t_counter	count;

	if (!str)
		return (FALSE);
	count.i = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\"')
				if (is_exit_code_expansion_condition(str, &count) == TRUE)
					return (TRUE);
			if (str[count.i] && str[count.i] == '\"')
				count.i++;
		}
		else if (str[count.i] == '\'')
			count.i = skip_squotes(str, count.i);
		else
			if (is_exit_code_expansion_condition(str, &count) == TRUE)
				return (TRUE);
	}
	return (FALSE);
}

char	*get_dollar_sign_v1(char *old_token,
	char *dollar_sign, t_counter *count)
{
	count->i++;
	while (old_token[count->i]
		&& old_token[count->i] != '\"' && count->trigger == 0)
	{
		if (old_token[count->i] == '$'
			&& old_token[count->i + 1]
			&& old_token[count->i + 1] != '?')
		{
			count->y = 0;
			count->z = length_of_dollar_sign(old_token + count->i);
			dollar_sign = malloc(sizeof(char) * (count->z) + 1);
			count->i++;
			while (old_token[count->i]
				&& (ft_isalnum(old_token[count->i])
					|| old_token[count->i] == '_'))
				dollar_sign[count->y++] = old_token[count->i++];
			dollar_sign[count->y] = '\0';
			count->trigger = 1;
		}
		else
			count->i++;
	}
	if (old_token[count->i] && old_token[count->i] == '\"')
		count->i++;
	return (dollar_sign);
}

char	*get_dollar_sign(char *old_token, char *dollar_sign, t_counter *count)
{
	while (old_token[count->i] && count->trigger == 0)
	{
		if (old_token[count->i] == '\"')
			dollar_sign = get_dollar_sign_v1(old_token, dollar_sign, count);
		else if (old_token[count->i] == '\'')
			count->i = skip_squotes(old_token, count->i);
		else if (old_token[count->i] == '$'
			&& old_token[count->i + 1] && old_token[count->i + 1] != '?')
		{
			count->y = 0;
			count->z = length_of_dollar_sign(old_token + count->i);
			dollar_sign = malloc(sizeof(char) * (count->z) + 1);
			count->i++;
			while (old_token[count->i]
				&& (ft_isalnum(old_token[count->i])
					|| old_token[count->i] == '_'))
				dollar_sign[count->y++] = old_token[count->i++];
			dollar_sign[count->y] = '\0';
			count->trigger = 1;
		}
		else
			count->i++;
	}
	return (dollar_sign);
}

char	*expand_token_v1(char *env_value,
	char *old_token, char *dollar_sign, t_counter *count)
{
	char	*new_token;

	new_token = NULL;
	if (env_value)
	{
		count->m = (ft_strlen(env_value)
				+ ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1));
		new_token = malloc(sizeof(char) * (ft_strlen(env_value)
					+ ft_strlen(old_token) - (ft_strlen(dollar_sign) + 1)) + 1);
	}
	else
	{
		count->m = (ft_strlen(old_token)
				- (ft_strlen(dollar_sign) + 1));
		new_token = malloc(sizeof(char)
				* (ft_strlen(old_token) - (ft_strlen(dollar_sign) - 1)) + 1);
	}
	if (dollar_sign)
		free(dollar_sign);
	return (new_token);
}

char	*expand_token_v2(char *env_value,
	char *new_token, char *old_token, t_counter *count)
{
	if (env_value && env_value[0])
		while (count->j < count->m && env_value[count->k])
			new_token[count->j++] = env_value[count->k++];
	count->i += length_of_dollar_sign(old_token + count->i) + 1;
	while (count->j < count->m && old_token[count->i])
		new_token[count->j++] = old_token[count->i++];
	new_token[count->j] = '\0';
	return (new_token);
}
