/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:53:25 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:53:35 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_env_variables_elseif(t_shell_s *minishell,
	char *old_token, t_counter *count)
{
	old_token = ft_strdup(minishell->lexer->raw_tokens[count->i]);
	free_and_null(minishell->lexer->raw_tokens[count->i]);
	minishell->lexer->raw_tokens[count->i]
		= expand_exit_code_token(minishell, old_token);
	free_and_null(old_token);
}

t_shell_s	*expand_env_variables(t_shell_s *minishell)
{
	t_counter	count;
	char		*old_token;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	while (minishell->lexer->tokens[count.i])
	{
		if (is_expandable(minishell->lexer->raw_tokens[count.i]) == TRUE)
		{
			old_token = ft_strdup(minishell->lexer->raw_tokens[count.i]);
			free_and_null(minishell->lexer->raw_tokens[count.i]);
			minishell->lexer->raw_tokens[count.i] = expand_token(old_token);
			free_and_null(old_token);
		}
		else if (is_exit_code_expansion(minishell->lexer->raw_tokens[count.i])
			== TRUE)
			expand_env_variables_elseif(minishell, old_token, &count);
		else
			count.i++;
	}
	return (minishell);
}

			// printf("%s\n", minishell->lexer->raw_tokens[count.i]);
void	token_size2_squotes(char *str, t_counter *count)
{
	count->i++;
	while (str[count->i] && str[count->i] != '\'')
	{
		count->counter++;
		count->i++;
	}
	if (str[count->i] && str[count->i] == '\'')
		count->i++;
}

void	token_size2_dquotes(char *str, t_counter *count)
{
	count->i++;
	while (str[count->i] && str[count->i] != '\"')
	{
		count->counter++;
		count->i++;
	}
	if (str[count->i] && str[count->i] == '\"')
		count->i++;
}

int	token_size2(char *str)
{
	t_counter	count;

	if (!str)
		return (0);
	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"')
			token_size2_dquotes(str, &count);
		else if (str[count.i] == '\'')
			token_size2_squotes(str, &count);
		else
		{
			count.counter++;
			count.i++;
		}
	}
	return (count.counter);
}
