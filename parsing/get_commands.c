/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:26:32 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:12:09 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_num_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	count.counter = 0;
	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens
		|| !minishell->lexer->raw_tokens[0])
		return (NULL);
	while (minishell->lexer->raw_tokens[count.i])
	{
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
		{
			while (minishell->lexer->raw_tokens[count.i]
				&& ft_strncmp(minishell->lexer->raw_tokens[count.i],
					"|\0", 2) != 0)
				count.i++;
			count.i--;
			count.counter++;
		}
		count.i++;
	}
	minishell->num_commands = count.counter;
	return (minishell);
}
	// printf("num of commands = %i\n", minishell->num_commands);
//  && minishell->lexer->tokens[count.i + 2]

int	check_if_command(t_shell_s *minishell, char *token, int token_num)
{
	if (!minishell || !token)
		return (FALSE);
	if (ft_strncmp(token, ">\0", 2) == 0 || ft_strncmp(token, "<\0", 2) == 0
		|| ft_strncmp(token, "|\0", 2) == 0
		|| ft_strncmp(token, ">>\0", 3) == 0
		|| ft_strncmp(token, "<<\0", 3) == 0)
		return (FALSE);
	if (token_num > 0
		&& (ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				">\0", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				"<\0", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				"<<\0", 3) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				">>\0", 3) == 0))
		return (FALSE);
	return (TRUE);
}

void	get_commands_v1(t_shell_s *minishell, t_counter *count)
{
	if (check_if_command(minishell,
			minishell->lexer->raw_tokens[count->i], count->i) == TRUE)
	{
		minishell->commands[count->j++]
			= ft_strdup(minishell->lexer->tokens[count->i]);
		while (minishell->lexer->tokens[count->i]
			&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"|\0", 2) != 0)
			count->i++;
		if (minishell->lexer->tokens[count->i]
			&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"|\0", 2) == 0)
			count->i++;
	}
	else if (ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
	{
		minishell->commands[count->j] = malloc(sizeof(char) * 1);
		minishell->commands[count->j++][0] = '\0';
		count->i++;
	}
	else
		count->i++;
}

t_shell_s	*get_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	minishell->commands = ft_calloc(sizeof(char *),
			(count_pipes(minishell->cmd_line) + 2));
	while (minishell->lexer->tokens[count.i])
		get_commands_v1(minishell, &count);
	return (minishell->commands[count.j] = NULL, minishell);
}
	// minishell->commands[count.j] = NULL;
	// for (int i = 0; i < minishell->num_commands
	// && minishell->commands[i]; i++)
	// 	printf("command[%i] = %s\n", i, minishell->commands[i]);