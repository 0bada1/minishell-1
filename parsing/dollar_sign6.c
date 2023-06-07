/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:34 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:55:39 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_token_counter_zero(t_counter *count)
{
	count->m = 0;
	count->i = 0;
	count->j = 0;
	count->k = 0;
}

int	expand_token_condition(char *old_token, t_counter *count)
{
	if (old_token[count->i] == '$'
		&& old_token[count->i + 1] && old_token[count->i + 1] != '?')
		return (TRUE);
	return (FALSE);
}

char	*expand_token_v3(char *new_token,
	char *env_value, char *old_token, t_counter *count)
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

char	*etlv1(char *new_token, char *env_value, char *old_token,
	t_counter *count)
{
	return (new_token = expand_token_v2(env_value,
			new_token, old_token, count), new_token);
}

char	*expand_token_loop(char *new, char *old_token, char *env_value,
	t_counter *count)
{
	while (old_token[count->i])
	{
		if (old_token[count->i] == '\"')
		{
			new[count->j++] = old_token[count->i++];
			while (old_token[count->i] && old_token[count->i] != '\"')
			{
				if (expand_token_condition(old_token, count) == TRUE)
					return (new = etlv1(new, env_value, old_token, count));
				else
					new[count->j++] = old_token[count->i++];
			}
			if (count->j < count->m && old_token[count->i]
				&& old_token[count->i] == '\"')
				new[count->j++] = old_token[count->i++];
		}
		else if (old_token[count->i] == '\'')
			count->i = skip_squotes(old_token, count->i);
		else if (expand_token_condition(old_token, count) == TRUE)
			return (new = expand_token_v3(new, env_value,
					old_token, count), new);
		else
			new[count->j++] = old_token[count->i++];
	}
	return (new);
}
