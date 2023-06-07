/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_lexer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:24:15 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:24:32 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*raw_lexer(t_shell_s *minishell, char *str)
{
	t_counter	c;

	if (!minishell || !minishell->lexer)
		return (NULL);
	if (!str)
		return (minishell);
	c.i = 0;
	c.j = 0;
	malloc_raw_lexer(minishell);
	while (str[c.i] && c.j < minishell->lexer->num_of_tokens)
		raw_lexer_loop(minishell, str, &c);
	return (minishell->lexer->raw_tokens[c.j] = NULL, minishell);
}
	// printf("num of tokens = %i\n", minishell->lexer->num_of_tokens);
			// printf("%c", str[count.i]);
			// printf("This is a heredoc\n");
		// printf("str[%i] = %c\n", count.i, str[count.i]);
	// for (int i = 0; minishell->lexer->raw_tokens[i]; i++)
	// 	printf("raw_tokens[%i] = %s\n", i, minishell->lexer->raw_tokens[i]);

void	raw_token_size_squote(char *str, t_counter *c)
{
	c->i++;
	c->length++;
	while (str[c->i] && str[c->i] != '\'')
	{
		c->length++;
		c->i++;
	}
	c->trigger = 1;
	c->length++;
	c->i++;
}

void	raw_token_size_dquote(char *str, t_counter *c)
{
	c->i++;
	c->length++;
	while (str[c->i] && str[c->i] != '\"')
	{
		c->length++;
		c->i++;
	}
	c->trigger = 1;
	c->length++;
	c->i++;
}

void	raw_token_size_trigger(t_counter *c)
{
	c->length++;
	c->i++;
}

int	raw_token_size(char *str, int i)
{
	t_counter	c;

	if (!str)
		return (0);
	c.length = 0;
	c.i = skip_spaces(str, i);
	while (str[c.i] && (str[c.i] != ' ' && str[c.i] != '\t'))
	{
		c.trigger = 0;
		if (str[c.i] == '\'')
			raw_token_size_squote(str, &c);
		else if (str[c.i] == '\"')
			raw_token_size_dquote(str, &c);
		if (c.length == 0 && is_heredoc_append(str, &c) == TRUE)
			return (2);
		else if (c.length != 0 && is_heredoc_append(str, &c) == TRUE)
			return (c.length);
		if (c.length == 0 && is_infile_outfile_pipe(str, &c) == TRUE)
			return (1);
		else if (c.length != 0 && is_infile_outfile_pipe(str, &c) == TRUE)
			return (c.length);
		if (c.trigger == 0)
			raw_token_size_trigger(&c);
	}
	return (c.length);
}
	// printf("token size = %i\n", length);
