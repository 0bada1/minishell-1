/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:25:36 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:09:09 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_num_flags(char **token, int i)
{
	t_counter	count;

	if (!token)
		return (0);
	count.counter = 0;
	while (token[i])
	{
		if ((ft_strncmp(token[i], ">\0", 2) == 0
				|| ft_strncmp(token[i], "<\0", 2) == 0
				|| ft_strncmp(token[i], "<<\0", 3) == 0
				|| ft_strncmp(token[i], ">>\0", 3) == 0))
			i++;
		else if (ft_strncmp(token[i], "|\0", 2) != 0)
			count.counter++;
		else if (ft_strncmp(token[i], "|\0", 2) == 0)
			break ;
		i++;
	}
	return (count.counter);
}
		// printf("token num = %i\n", i);
		// printf("token in get_num_flags = %s\n", token[i]);
	// printf("num of args = %i\n", count.counter);

void	get_flags_v3(t_shell_s *minishell, t_counter *count)
{
	while (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) != 0)
	{
		if (check_if_command(minishell,
				minishell->lexer->raw_tokens[count->i], count->i) == TRUE)
			minishell->flags[count->j][count->k++]
				= ft_strdup(minishell->lexer->tokens[count->i++]);
		else
			count->i++;
	}
	if (minishell->lexer->raw_tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
		count->i++;
	minishell->flags[count->j++][count->k] = NULL;
}

void	get_flags_v2(t_shell_s *minishell, t_counter *count)
{
	minishell->flags[count->j++][count->k] = NULL;
	while (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) != 0)
		count->i++;
	if (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
		count->i++;
}

void	get_flags_v1(t_shell_s *minishell, t_counter *count)
{
	count->k = 0;
	minishell->flags[count->j]
		= ft_calloc(sizeof(char *),
			get_num_flags(minishell->lexer->raw_tokens, count->i) + 1);
	if (get_num_flags(minishell->lexer->raw_tokens, count->i) == 0)
		get_flags_v2(minishell, count);
	else
	{
		get_flags_v3(minishell, count);
	}
}

t_shell_s	*get_flags(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	minishell->flags = malloc(sizeof(char **)
			* (count_pipes(minishell->cmd_line) + 2));
	while (minishell->lexer->tokens[count.i])
		get_flags_v1(minishell, &count);
	minishell->flags[count.j] = NULL;
	return (minishell);
}
	// printf("count.j in get_flags = %i && number of commands = %i\n",
	// count.j, count_pipes(minishell->cmd_line) + 1);
	// for (int k = 0; minishell->flags[k]; k++)
	// 	for (int j = 0; minishell->flags[k][j]; j++)
	// 		printf("args[%i][%i] = %s\n", k, j, minishell->flags[k][j]);
// < infile hello "world"| does < infile this work?
