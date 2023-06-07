/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_to_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:50:44 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 13:50:51 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	length_to_pipe_dquotes(char *str, t_counter *count)
{
	count->i++;
	count->length++;
	while (str[count->i] && str[count->i] != '\"')
	{
		count->length++;
		count->i++;
	}
	count->length++;
	count->i++;
	count->trigger = 1;
}

void	length_to_pipe_squotes(char *str, t_counter *count)
{
	count->i++;
	count->length++;
	while (str[count->i] && str[count->i] != '\'')
	{
		count->length++;
		count->i++;
	}
	if (str[count->i] && str[count->i] == '\'')
	{
		count->i++;
		count->length++;
	}
	count->trigger = 1;
}

// length and i are the same number so use one
int	length_to_pipe(char *str, int i)
{
	t_counter	count;

	if (!str)
		return (0);
	count.length = 0;
	count.i = i;
	while (str[count.i])
	{
		count.trigger = 0;
		if (str[count.i] == '\"')
			length_to_pipe_dquotes(str, &count);
		else if (str[count.i] == '\'')
			length_to_pipe_squotes(str, &count);
		if (str[count.i] == '|' && count.trigger == 0)
			break ;
		if (count.trigger == 0)
		{
			count.i++;
			count.length++;
		}
	}
	return (count.length);
}
	// printf("count.length to pipe = %i\n", count.length);
	// printf("i = %i\n", i);