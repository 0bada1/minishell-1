/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:51:39 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:16:57 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	num_of_tokens_to_pipe(char **tokens, int token_num)
{
	t_counter	count;

	if (!tokens || !tokens[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (tokens[token_num])
	{
		if (ft_strncmp(tokens[token_num], "|\0", 2) == 0)
			break ;
		count.counter++;
		token_num++;
	}
	return (count.counter);
}
	// printf("num of tokens till pipe = %i\n", count.counter);

char	**split_raw_command_block(t_shell_s *minishell, int token_num)
{
	t_counter	count;
	char		**command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	command_block = ft_calloc(sizeof(char *),
			num_of_tokens_to_pipe(minishell->lexer->raw_tokens, token_num) + 1);
	while (minishell->lexer->raw_tokens[token_num]
		&& ft_strncmp(minishell->lexer->raw_tokens[token_num], "|\0", 2) != 0)
	{
		command_block[count.i]
			= ft_strdup(minishell->lexer->raw_tokens[token_num]);
		count.i++;
		token_num++;
	}
	return (command_block);
}

char	**split_command_block(t_shell_s *minishell, int token_num)
{
	t_counter	count;
	char		**command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	command_block = ft_calloc(sizeof(char *),
			num_of_tokens_to_pipe(minishell->lexer->raw_tokens, token_num) + 1);
	while (minishell->lexer->tokens[token_num]
		&& ft_strncmp(minishell->lexer->raw_tokens[token_num], "|\0", 2) != 0)
	{
		command_block[count.i] = ft_strdup(minishell->lexer->tokens[token_num]);
		count.i++;
		token_num++;
	}
	return (command_block);
}

int	number_of_squotes(char *str)
{
	t_counter	count;

	count.i = 0;
	count.counter = 0;
	count.trigger = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\"' && count.counter % 2 == 0)
		{
			if (count.trigger == 0)
				count.trigger = 1;
			else
				count.trigger = 0;
		}
		if (str[count.i] == '\'' && count.trigger == 0)
			count.counter++;
		count.i++;
	}
	return (count.counter);
}

int	number_of_dquotes(char *str)
{
	t_counter	count;

	count.i = 0;
	count.counter = 0;
	count.trigger = 0;
	while (str[count.i])
	{
		if (str[count.i] == '\'' && count.counter % 2 == 0)
		{
			if (count.trigger == 0)
				count.trigger = 1;
			else
				count.trigger = 0;
		}
		if (str[count.i] == '\"' && count.trigger == 0)
			count.counter++;
		count.i++;
	}
	return (count.counter);
}
