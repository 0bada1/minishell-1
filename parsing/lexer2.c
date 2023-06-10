/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:22:38 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:23:16 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
