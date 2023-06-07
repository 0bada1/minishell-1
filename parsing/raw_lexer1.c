/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_lexer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:39:46 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:24:02 by ooutabac         ###   ########.fr       */
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
