/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:33:52 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 13:33:58 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
