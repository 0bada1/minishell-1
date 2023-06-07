/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:19:00 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 14:09:37 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	skip_token(char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] == '\'' || str[i] == '\"')
				i++;
		}
		else
			i++;
	}
	return (i);
}
		// printf("str[%i]2 = %c\n", i, str[i]);

int	skip_symbols(char *str, int i)
{
	if (!str || !str[0])
		return (i);
	if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
		i += 2;
	else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		i += 2;
	else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		i++;
	return (i);
}

int	skip_squotes(char *str, int i)
{
	if (!str || i < 0)
		return (0);
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] && str[i] == '\'')
			i++;
	}
	return (i);
}

int	skip_dquotes(char *str, int i)
{
	if (!str || i < 0)
		return (0);
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] && str[i] == '\"')
			i++;
	}
	return (i);
}
