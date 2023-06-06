/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:38 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 16:56:25 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	num_of_tokens_loop(char *str, t_counter *count)
{
	while (str[count->i])
	{
		if (str[count->i] == '\"')
			count->i = skip_dquotes(str, count->i);
		else if (str[count->i] == '\'')
			count->i = skip_squotes(str, count->i);
		else if (str[count->i] == '>' || str[count->i] == '<'
			|| str[count->i] == '|')
		{
			count->counter++;
			if (count->i > 0 && str[count->i - 1] != ' '
				&& str[count->i - 1] != '\t')
				count->counter++;
			count->i = skip_symbols(str, count->i);
			count->i = skip_spaces(str, count->i);
		}
		else if (str[count->i] != ' ' && str[count->i] != '\t')
			count->i++;
		else if (str[count->i] == ' ' || str[count->i] == '\t')
		{
			count->counter++;
			count->i = skip_spaces(str, count->i);
		}
	}
}

int	num_of_tokens(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 1;
	num_of_tokens_loop(str, &count);
	return (count.counter);
}

int	is_heredoc_append(char *str, t_counter *c)
{
	if ((str[c->i] == '>'
			&& str[c->i + 1] && str[c->i + 1] == '>')
		|| (str[c->i] == '<'
			&& str[c->i + 1] && str[c->i + 1] == '<'))
		return (TRUE);
	return (FALSE);
}

int	is_infile_outfile_pipe(char *str, t_counter *c)
{
	if (str[c->i] == '>' || str[c->i] == '<' || str[c->i] == '|')
		return (TRUE);
	return (FALSE);
}

void	token_size_squote(char *str, t_counter *c)
{
	c->i++;
	while (str[c->i] && str[c->i] != '\'')
	{
		c->length++;
		c->i++;
	}
	c->i++;
	c->trigger = 1;
}

void	token_size_dquote(char *str, t_counter *c)
{
	c->i++;
	while (str[c->i] && str[c->i] != '\"')
	{
		c->length++;
		c->i++;
	}
	c->i++;
	c->trigger = 1;
}

void	token_size_trigger(t_counter *c)
{
	c->length++;
	c->i++;
}

int	token_size(char *str, int i)
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
			token_size_squote(str, &c);
		else if (str[c.i] == '\"')
			token_size_dquote(str, &c);
		if (c.length == 0 && is_heredoc_append(str, &c) == TRUE)
			return (2);
		else if (c.length != 0 && is_heredoc_append(str, &c) == TRUE)
			return (c.length);
		if (c.length == 0 && is_infile_outfile_pipe(str, &c) == TRUE)
			return (1);
		else if (c.length != 0 && is_infile_outfile_pipe(str, &c) == TRUE)
			return (c.length);
		if (c.trigger == 0)
			token_size_trigger(&c);
	}
	return (c.length);
}
	// printf("token size = %i\n", length);

int	check_for_dquotes(char *str, int i)
{
	if (!str)
		return (FALSE);
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == '\"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
