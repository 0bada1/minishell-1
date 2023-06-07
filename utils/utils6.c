/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:28:56 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 20:45:11 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*malloc_raw_lexer(t_shell_s *minishell)
{
	minishell->lexer->raw_tokens = ft_calloc(sizeof(char *),
			(minishell->lexer->num_of_tokens + 1));
	minishell->lexer->raw_tokens[0] = NULL;
	return (minishell);
}

void	raw_lexer_double_symbol(t_shell_s *minishell,
		t_counter *c, char *str)
{
	free_and_null(minishell->lexer->raw_tokens[c->j]);
	minishell->lexer->raw_tokens[c->j] = malloc(sizeof(char) * (3));
	minishell->lexer->raw_tokens[c->j][0] = str[c->i];
	minishell->lexer->raw_tokens[c->j][1] = str[c->i + 1];
	minishell->lexer->raw_tokens[c->j++][2] = '\0';
	c->i = skip_symbols(str, c->i);
}

void	raw_lexer_single_symbol(t_shell_s *minishell,
		t_counter *c, char *str)
{
	free_and_null(minishell->lexer->raw_tokens[c->j]);
	minishell->lexer->raw_tokens[c->j] = malloc(sizeof(char) * (2));
	minishell->lexer->raw_tokens[c->j][0] = str[c->i];
	minishell->lexer->raw_tokens[c->j++][1] = '\0';
	c->i = skip_symbols(str, c->i);
}

void	raw_lexer_loop2(t_shell_s *minishell, char *str, t_counter *c)
{
	while (str[c->i] && c->j < minishell->lexer->num_of_tokens)
	{
		if (str[c->i] == '\"')
		{
			minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
			while (str[c->i] && str[c->i] != '\"')
				minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
			minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
		}
		else if (str[c->i] == '\'')
		{
			minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
			while (str[c->i] && str[c->i] != '\'')
				minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
			minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
		}
		else if (str[c->i] == '<' || str[c->i] == '>' || str[c->i] == '|')
			break ;
		else if (str[c->i] != ' ' && str[c->i] != '\t')
			minishell->lexer->raw_tokens[c->j][c->k++] = str[c->i++];
		else if (str[c->i] == ' ' || str[c->i] == '\t')
			break ;
	}
}

void	raw_lexer_loop(t_shell_s *minishell, char *str, t_counter *c)
{
	minishell->lexer->raw_tokens[c->j] = ft_calloc(sizeof(char),
			raw_token_size(str, c->i) + 1);
	c->k = 0;
	c->trigger = 0;
	raw_lexer_loop2(minishell, str, c);
	if (c->k > 0)
		minishell->lexer->raw_tokens[c->j++][c->k] = '\0';
	if ((str[c->i] == '>' && str[c->i + 1] && str[c->i + 1] == '>')
		|| (str[c->i] == '<' && str[c->i + 1] && str[c->i + 1] == '<'))
		raw_lexer_double_symbol(minishell, c, str);
	else if (str[c->i] == '>' || str[c->i] == '<' || str[c->i] == '|')
		raw_lexer_single_symbol(minishell, c, str);
	c->i = skip_spaces(str, c->i);
}

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

char	**skip_double_quote_and_assign(
				t_counter *count, char *str, char **blocks)
{
	blocks[count->j][count->k++] = str[count->i++];
	while (str[count->i] && str[count->i] != '\"')
		blocks[count->j][count->k++] = str[count->i++];
	if (str[count->i] && str[count->i] == '\"')
		blocks[count->j][count->k++] = str[count->i++];
	return (blocks);
}

char	**skip_single_quote_and_assign(
				t_counter *count, char *str, char **blocks)
{
	blocks[count->j][count->k++] = str[count->i++];
	while (str[count->i] && str[count->i] != '\'')
		blocks[count->j][count->k++] = str[count->i++];
	if (str[count->i] && str[count->i] == '\'')
		blocks[count->j][count->k++] = str[count->i++];
	return (blocks);
}

char	**split_pipes_loop(char *str, char **blocks, t_counter *count)
{
	while (str[count->i])
	{
		count->trigger = 0;
		count->k = 0;
		blocks[count->j] = ft_calloc(sizeof(char),
				length_to_pipe(str, count->i) + 1);
		while (str[count->i])
		{
			if (str[count->i] == '\"')
				blocks = skip_double_quote_and_assign(count, str, blocks);
			else if (str[count->i] == '\'')
				blocks = skip_single_quote_and_assign(count, str, blocks);
			else if (str[count->i] == '|' && count->trigger == 0)
			{
				count->i++;
				count->i = skip_spaces(str, count->i);
				break ;
			}
			else
				blocks[count->j][count->k++] = str[count->i++];
		}
		blocks[count->j++][count->k] = '\0';
	}
	return (blocks[count->j] = NULL, blocks);
}

char	**split_pipes(char	*str)
{
	char		**blocks;
	t_counter	count;

	if (!str || !str[0])
		return (NULL);
	count.i = 0;
	count.j = 0;
	blocks = ft_calloc(sizeof(char *), count_pipes(str) + 2);
	if (!blocks)
		return (NULL);
	blocks = split_pipes_loop(str, blocks, &count);
	return (blocks);
}
	// for (int i = 0; blocks[i]; i++)
		// printf("block[%i] = %s\n", i, blocks[i]);

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

void	length_to_pipe_dquotes(char *str, t_counter *count)
{
	count->i++;
	count->length++;
	while (str[count->i] && str[count->i] != '\"')
	{
		count->length++;
		count->i++;
	}
	count->length++;
	count->i++;
	count->trigger = 1;
}

void	length_to_pipe_squotes(char *str, t_counter *count)
{
	count->i++;
	count->length++;
	while (str[count->i] && str[count->i] != '\'')
	{
		count->length++;
		count->i++;
	}
	if (str[count->i] && str[count->i] == '\'')
	{
		count->i++;
		count->length++;
	}
	count->trigger = 1;
}

// length and i are the same number so use one
int	length_to_pipe(char *str, int i)
{
	t_counter	count;

	if (!str)
		return (0);
	count.length = 0;
	count.i = i;
	while (str[count.i])
	{
		count.trigger = 0;
		if (str[count.i] == '\"')
			length_to_pipe_dquotes(str, &count);
		else if (str[count.i] == '\'')
			length_to_pipe_squotes(str, &count);
		if (str[count.i] == '|' && count.trigger == 0)
			break ;
		if (count.trigger == 0)
		{
			count.i++;
			count.length++;
		}
	}
	return (count.length);
}
	// printf("count.length to pipe = %i\n", count.length);
	// printf("i = %i\n", i);