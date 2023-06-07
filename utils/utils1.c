/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:35:50 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/04 23:22:38 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipes_valid(char *str)
{
	t_counter	count;

	count.i = 0;
	count.trigger = 0;
	while (str[count.i] && count.trigger == 0)
	{
		if (str[count.i] == '|')
		{
			count.i = skip_spaces(str, count.i);
			if (str[count.i] == '|'
				|| str[count.i] == '>' || str[count.i] == '<')
				count.trigger = -1;
		}
	}
	return (count.trigger);
}

int	ft_strlen_spaces(char *str, int i)
{
	int	length;

	length = 0;
	while (str[i] && (str[i] != ' ' || str[i] != '\t'))
	{
		length++;
		i++;
	}
	return (length);
}

int	count_pipes(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		count.trigger = 0;
		if (str[count.i] == '\"')
		{
			count.i = skip_dquotes(str, count.i);
			count.trigger = 1;
		}
		else if (str[count.i] == '\'')
		{
			count.i = skip_squotes(str, count.i);
			count.trigger = 1;
		}
		if (str[count.i] == '|' && count.trigger == 0)
			count.counter++;
		if (count.trigger == 0)
			count.i++;
	}
	return (count.counter);
}
		// if(str[count.i] == '\'' || str[count.i] == '"')
		// {
		// 	if(quote == str[count.i])
		// 		quote = 0;
		// 	else
		// 		quote = str[count.i];
		// }
		// if (str[count.i] == '|' && quote == 0)
		// 	count.counter++;
		// count.i++;

int	count_tokens(char *str)
{
	t_counter	count;

	if (!str)
		return (0);
	count.i = 0;
	count.counter = 1;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
			count.i = skip_dquotes(str, count.i);
		else if (str[count.i] == '\'')
			count.i = skip_squotes(str, count.i);
		else if (str[count.i] != ' ' && str[count.i] != '\t')
			count.i++;
		else if (str[count.i] == ' ' || str[count.i] == '\t')
		{
			count.i = skip_spaces(str, count.i);
			count.counter++;
		}
	}
	if (count.i == 0)
		return (0);
	return (count.counter);
}

int	ft_strlen_equals(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
