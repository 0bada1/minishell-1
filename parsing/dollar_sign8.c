/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:56:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:57:05 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_expandable_condition2(char *str, t_counter *count)
{
	if (str[count->i] == '$' && str[count->i + 1]
		&& (ft_isalnum(str[count->i + 1]) == 1
			|| str[count->i + 1] == '_'))
		return (TRUE);
	return (FALSE);
}

int	is_expandable(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (FALSE);
	count.i = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
		{
			count.i++;
			while (str[count.i] && str[count.i] != '\"')
				if (is_expandable_condition(str, &count) == TRUE)
					return (TRUE);
			if (str[count.i] && str[count.i] == '\"')
				count.i++;
		}
		else if (str[count.i] == '\'')
			count.i = skip_squotes(str, count.i);
		else if (is_expandable_condition2(str, &count) == TRUE)
			return (TRUE);
		else
			count.i++;
	}
	return (FALSE);
}
// printf("%s is expandable and isalnum = %i\n", str,
// ft_isalnum(str[count.i + 1])),
// printf("%s is not expandable\n", str),

int	number_of_expansions(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\'')
			count.i = skip_squotes(str, count.i);
		else if (str[count.i] == '$')
		{
			count.counter++;
			count.i++;
			while (str[count.i] && (ft_isalnum(str[count.i]) == 1
					|| str[count.i] == '_'))
				count.i++;
		}
		else
			count.i++;
	}
	return (count.counter);
}

int	is_exit_code_expansion_condition(char *str, t_counter *count)
{
	if (str[count->i] == '$' && str[count->i + 1] && str[count->i + 1] == '?')
		return (TRUE);
	count->i++;
	return (FALSE);
}

int	is_exit_code_expansion_condition2(char *str, t_counter *count)
{
	if (str[count->i] == '$' && str[count->i + 1] && str[count->i + 1] == '?')
		return (TRUE);
	return (FALSE);
}
