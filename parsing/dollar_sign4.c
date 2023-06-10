/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:54:14 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:59:20 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

int	exit_expansion_token_size(t_shell_s *minishell, char *str)
{
	t_counter	count;
	char		*tmp;

	(void)minishell;
	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	tmp = NULL;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
			exit_expansion_token_size_dquote(str, tmp, &count);
		else if (str[count.i] == '\'')
			exit_expansion_token_size_squote(str, &count);
		else
			exit_expansion_token_size_else(str, tmp, &count);
	}
	return (count.counter);
}

char	*expand_exit_code_token_dquote(t_shell_s *minishell,
	char *str, char *new_str, t_counter *count)
{
	char	*exit_code;

	(void)minishell;
	exit_code = ft_itoa(g_exit_code);
	new_str[count->j++] = str[count->i++];
	while (str[count->i] && str[count->i] != '\"')
	{
		if (is_exit_code_expansion_condition2(str, count) == TRUE)
		{
			count->k = 0;
			while (exit_code[count->k])
				new_str[count->j++] = exit_code[count->k++];
			count->i += 2;
		}
		else
			new_str[count->j++] = str[count->i++];
	}
	if (str[count->i] && str[count->i] == '\"')
		new_str[count->j++] = str[count->i++];
	free_and_null(exit_code);
	return (new_str);
}

char	*expand_exit_code_token_squote(char *str,
	char *new_str, t_counter *count)
{
	new_str[count->j++] = str[count->i++];
	while (str[count->i] && str[count->i] != '\'')
		new_str[count->j++] = str[count->i++];
	if (str[count->i] && str[count->i] == '\'')
		new_str[count->j++] = str[count->i++];
	return (new_str);
}

char	*expand_exit_code_token_else(char *str,
	char *new_str, char *exit_code, t_counter *count)
{
	if (is_exit_code_expansion_condition2(str, count) == TRUE)
	{
		count->k = 0;
		while (exit_code[count->k])
			new_str[count->j++] = exit_code[count->k++];
		count->i += 2;
	}
	else
		new_str[count->j++] = str[count->i++];
	return (new_str);
}

char	*expand_exit_code_token(t_shell_s *minishell, char *str)
{
	t_counter	count;
	char		*new_str;
	char		*exit_code;

	if (!str || !str[0])
		return (NULL);
	count.i = 0;
	count.j = 0;
	exit_code = ft_itoa(g_exit_code);
	new_str = malloc(sizeof(char)
			* (exit_expansion_token_size(minishell, str)) + 1);
	while (str[count.i])
	{
		if (str[count.i] == '\"')
			new_str = expand_exit_code_token_dquote(minishell,
					str, new_str, &count);
		else if (str[count.i] == '\'')
			new_str = expand_exit_code_token_squote(str, new_str, &count);
		else
			new_str = expand_exit_code_token_else(str,
					new_str, exit_code, &count);
	}
	new_str[count.j] = '\0';
	free(exit_code);
	return (new_str);
}
