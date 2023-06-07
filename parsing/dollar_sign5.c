/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:54:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:59:35 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

void	expand_token_initialize(void *dollar_sign,
	void *new_token, t_counter *count)
{
	count->i = 0;
	count->trigger = 0;
	dollar_sign = NULL;
	new_token = NULL;
}

char	*expand_token(char *old_token)
{
	t_counter	count;
	char		*new_token;
	char		*env_value;
	char		*dollar_sign;

	if (!old_token)
		return (NULL);
	expand_token_initialize(&dollar_sign, &new_token, &count);
	dollar_sign = get_dollar_sign(old_token, dollar_sign, &count);
	env_value = getenv(dollar_sign);
	expand_token_counter_zero(&count);
	new_token = expand_token_v1(env_value, old_token, dollar_sign, &count);
	new_token = expand_token_loop(new_token, old_token, env_value, &count);
	return (new_token[count.j] = '\0', new_token);
}
// , free(old_token)

void	exit_expansion_token_size_squote(char *str, t_counter *count)
{
	count->i++;
	count->counter++;
	while (str[count->i] && str[count->i] != '\'')
	{
		count->i++;
		count->counter++;
	}
	if (str[count->i] && str[count->i] == '\'')
	{
		count->i++;
		count->counter++;
	}
}

void	exit_expansion_token_size_dquote(char *str, char *tmp, t_counter *count)
{
	count->i++;
	count->counter++;
	while (str[count->i] && str[count->i] != '\"')
	{
		if (is_exit_code_expansion_condition2(str, count) == TRUE)
		{
			tmp = ft_itoa(g_exit_code);
			count->counter += ft_strlen(tmp);
			free(tmp);
			count->i += 2;
		}
		else
		{
			count->i++;
			count->counter++;
		}
	}
	if (str[count->i] && str[count->i] == '\"')
	{
		count->i++;
		count->counter++;
	}
}

void	exit_expansion_token_size_else(char *str, char *tmp, t_counter *count)
{
	if (is_exit_code_expansion_condition2(str, count) == TRUE)
	{
		tmp = ft_itoa(g_exit_code);
		count->counter += ft_strlen(tmp);
		free(tmp);
		count->i += 2;
	}
	else
	{
		count->i++;
		count->counter++;
	}
}
