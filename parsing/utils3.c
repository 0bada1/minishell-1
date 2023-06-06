/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:48:06 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 16:38:59 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*malloc_lexer(t_shell_s *minishell, char *str)
{
	minishell->lexer = ft_calloc(sizeof(t_lexer), 1);
	minishell->lexer->num_of_tokens = num_of_tokens(str);
	minishell->lexer->tokens
		= ft_calloc(sizeof(char *), (minishell->lexer->num_of_tokens + 1));
	minishell->lexer->tokens[0] = NULL;
	return (minishell);
}

void	lexer_dquotes_assign(t_shell_s *minishell, t_counter *c, char *str)
{
	c->i++;
	while (str[c->i] && str[c->i] != '\"')
	{
		minishell->lexer->tokens[c->j][c->k++]
			= str[c->i++];
		c->m++;
	}
	c->i++;
}

void	lexer_squotes_assign(t_shell_s *minishell, t_counter *c, char *str)
{
	c->i++;
	while (str[c->i] && str[c->i] != '\'')
	{
		minishell->lexer->tokens[c->j][c->k++]
			= str[c->i++];
		c->m++;
	}
	c->i++;
}

void	lexer_double_symbol(t_shell_s *minishell,
		t_counter *c, char *str)
{
	free_and_null(minishell->lexer->tokens[c->j]);
	minishell->lexer->tokens[c->j] = malloc(sizeof(char) * (3));
	minishell->lexer->tokens[c->j][0] = str[c->i];
	minishell->lexer->tokens[c->j][1] = str[c->i + 1];
	minishell->lexer->tokens[c->j++][2] = '\0';
	c->i = skip_symbols(str, c->i);
}

void	lexer_not_space_tab(t_shell_s *minishell, t_counter *c, char *str)
{
	minishell->lexer->tokens[c->j][c->k++] = str[c->i++];
	c->m++;
}

void	lexer_single_symbol(t_shell_s *minishell,
		t_counter *c, char *str)
{
	free_and_null(minishell->lexer->tokens[c->j]);
	minishell->lexer->tokens[c->j] = malloc(sizeof(char) * (2));
	minishell->lexer->tokens[c->j][0] = str[c->i];
	minishell->lexer->tokens[c->j++][1] = '\0';
	c->i = skip_symbols(str, c->i);
}

void	lexer_loop2(t_shell_s *minishell, char *str, t_counter *c)
{
	while (str[c->i] && c->j < minishell->lexer->num_of_tokens)
	{
		if (str[c->i] == '\"')
			lexer_dquotes_assign(minishell, c, str);
		else if (str[c->i] == '\'')
			lexer_squotes_assign(minishell, c, str);
		else if (str[c->i] == '<' || str[c->i] == '>'
			|| str[c->i] == '|')
			break ;
		else if (str[c->i] != ' ' && str[c->i] != '\t')
			lexer_not_space_tab(minishell, c, str);
		else if (str[c->i] == ' ' || str[c->i] == '\t')
			break ;
	}
}

void	lexer_loop(t_shell_s *minishell, char *str, t_counter *c)
{
	minishell->lexer->tokens[c->j]
		= ft_calloc(sizeof(char), token_size(str, c->i) + 1);
	c->k = 0;
	c->m = c->i;
	lexer_loop2(minishell, str, c);
	if (c->k > 0)
		minishell->lexer->tokens[c->j++][c->k] = '\0';
	else if (c->k == 0 && c->i > c->m)
		minishell->lexer->tokens[c->j++][c->k] = '\0';
	if ((str[c->i] == '>' && str[c->i + 1]
			&& str[c->i + 1] == '>') || (str[c->i] == '<'
			&& str[c->i + 1] && str[c->i + 1] == '<'))
		lexer_double_symbol(minishell, c, str);
	else if (str[c->i] == '>' || str[c->i] == '<'
		|| str[c->i] == '|')
		lexer_single_symbol(minishell, c, str);
	c->i = skip_spaces(str, c->i);
}

/* LEXER
How it works:
1)
*/
t_shell_s	*lexer(t_shell_s *minishell, char *str)
{
	t_counter	c;

	if (!minishell)
		return (NULL);
	if (!str)
		return (minishell);
	c.i = 0;
	c.j = 0;
	minishell = malloc_lexer(minishell, str);
	while (str[c.i] && c.j < minishell->lexer->num_of_tokens)
		lexer_loop(minishell, str, &c);
	return (minishell->lexer->tokens[c.j] = NULL, minishell);
}
	// printf("num of tokens = %i\n", minishell->lexer->num_of_tokens);
		// printf("Token size = %i\n", token_size(str, c.i));
		// printf("token size in lexer = %i\n", token_size(str, c.i));
	// 	printf("tokens[%i] = %s\n", i, minishell->lexer->tokens[i]);
	// for (int i = 0; minishell->lexer->tokens[i]; i++)
	// 	printf("tokens[%i] = %s\n", i, minishell->lexer->tokens[i]);

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

// void	print_struct(t_shell_s *args)
// {

// 	t_counter	counter;

// 	counter.i = 0;
// 	counter.j = 0;
// 	counter.k = 0;
// 	counter.m = 0;
// 	counter.n = 0;
// 	printf("\nNUMBER OF COMMANDS: %i\n", args->num_commands);
// 	printf("\nNUMBER OF PIPES: %i\n", args->num_pipes);
// 	printf("\nPRINTING COMMANDS:\n");
// 	while (counter.i < args->num_commands)
// 		printf("%s\n", args->commands[counter.i++]);
// 	// printf("\nPRINTING RAW COMMANDS:\n");
// 	// while (counter.n < args->num_commands)
// 	// 	printf("%s\n", args->cmd_raw[counter.n++]);
// 	// printf("\nPRINTING COMMANDS PATH:\n");
// 	// while (counter.j < args->num_commands)
// 	// 	printf("%s\n", args->cmd_path[counter.j++]);
// 	// printf("\nPRINTING COMMANDS WITH NO FLAGS:\n");
// 	// while (counter.k < args->num_commands)
// 	// 	printf("%s\n", args->cmd_noflag[counter.k++]);
// 	// printf("\nPRINTING FULL PATH:\n%s\n", args->full_path);
// 	printf("\nPRINTING HOME:\n");
// 	printf("\nPRINTING SPLIT PATHS:\n");
// 	while (args->path[counter.m])
// 		printf("%s\n", args->path[counter.m++]);
// 	printf("\n\n");
// 	return ;
// }