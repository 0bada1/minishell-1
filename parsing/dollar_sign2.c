/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:52:10 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 18:53:03 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	assign_tokens_dquotes(t_shell_s *minishell, t_counter *count)
{
	count->j++;
	while (minishell->lexer->raw_tokens[count->i][count->j]
		&& minishell->lexer->raw_tokens[count->i][count->j] != '\"')
		minishell->lexer->tokens[count->i][count->k++]
			= minishell->lexer->raw_tokens[count->i][count->j++];
	if (minishell->lexer->raw_tokens[count->i][count->j]
		&& minishell->lexer->raw_tokens[count->i][count->j] == '\"')
		count->j++;
}

void	assign_tokens_squotes(t_shell_s *minishell, t_counter *count)
{
	count->j++;
	while (minishell->lexer->raw_tokens[count->i][count->j]
		&& minishell->lexer->raw_tokens[count->i][count->j] != '\'')
		minishell->lexer->tokens[count->i][count->k++]
			= minishell->lexer->raw_tokens[count->i][count->j++];
	if (minishell->lexer->raw_tokens[count->i][count->j]
		&& minishell->lexer->raw_tokens[count->i][count->j] == '\'')
		count->j++;
}

void	assign_tokens_loop(t_shell_s *minishell, t_counter *count)
{
	while (minishell->lexer->raw_tokens[count->i])
	{
		free_and_null(minishell->lexer->tokens[count->i]);
		minishell->lexer->tokens[count->i] = malloc(sizeof(char)
				* (token_size2(minishell->lexer->raw_tokens[count->i])) + 1);
		count->k = 0;
		count->j = 0;
		while (minishell->lexer->raw_tokens[count->i][count->j])
		{
			if (minishell->lexer->raw_tokens[count->i][count->j] == '\"')
				assign_tokens_dquotes(minishell, count);
			else if (minishell->lexer->raw_tokens[count->i][count->j] == '\'')
				assign_tokens_squotes(minishell, count);
			else
				minishell->lexer->tokens[count->i][count->k++]
					= minishell->lexer->raw_tokens[count->i][count->j++];
		}
		minishell->lexer->tokens[count->i][count->k] = '\0';
		count->i++;
	}
	minishell->lexer->tokens[count->i] = NULL;
}

t_shell_s	*assign_tokens(t_shell_s *minishell)
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	if (!minishell->lexer || !minishell->lexer->raw_tokens)
		return (minishell);
	count.i = 0;
	count.j = 0;
	assign_tokens_loop(minishell, &count);
	return (minishell);
}
	// printf("token[%i] = %s\n", count.i, minishell->lexer->tokens[count.i]);
	// for (int i = 0; i < minishell->lexer->num_of_tokens; i++)
	// 	printf("Token[%i] = %s\n", i, minishell->lexer->tokens[i]);

char	*dollar_sign(t_shell_s *minishell, char *cmd_line)
{
	char	*old_cmd_line;
	char	*new_cmd_line;

	if (!minishell)
		return (NULL);
	new_cmd_line = ft_strdup(cmd_line);
	old_cmd_line = ft_strdup(new_cmd_line);
	while (is_expandable(new_cmd_line) == TRUE)
	{
		free(new_cmd_line);
		new_cmd_line = expand_token(old_cmd_line);
		free_and_null(old_cmd_line);
		if (new_cmd_line)
			old_cmd_line = ft_strdup(new_cmd_line);
	}
	if (old_cmd_line != NULL)
		free(old_cmd_line);
	while (is_exit_code_expansion(new_cmd_line) == TRUE)
	{
		old_cmd_line = ft_strdup(new_cmd_line);
		free(new_cmd_line);
		new_cmd_line = expand_exit_code_token(minishell, old_cmd_line);
		free(old_cmd_line);
	}
	return (new_cmd_line);
}
