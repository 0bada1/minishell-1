/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:29:10 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:23:24 by ooutabac         ###   ########.fr       */
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