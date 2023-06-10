/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:32:07 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 13:32:16 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	num_of_tokens_loop(char *str, t_counter *count)
{
	while (str[count->i])
	{
		if (str[count->i] == '\"')
			count->i = skip_dquotes(str, count->i);
		else if (str[count->i] == '\'')
			count->i = skip_squotes(str, count->i);
		else if (str[count->i] == '>' || str[count->i] == '<'
			|| str[count->i] == '|')
		{
			count->counter++;
			if (count->i > 0 && str[count->i - 1] != ' '
				&& str[count->i - 1] != '\t')
				count->counter++;
			count->i = skip_symbols(str, count->i);
			count->i = skip_spaces(str, count->i);
		}
		else if (str[count->i] != ' ' && str[count->i] != '\t')
			count->i++;
		else if (str[count->i] == ' ' || str[count->i] == '\t')
		{
			count->counter++;
			count->i = skip_spaces(str, count->i);
		}
	}
}

int	num_of_tokens(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 1;
	num_of_tokens_loop(str, &count);
	return (count.counter);
}
