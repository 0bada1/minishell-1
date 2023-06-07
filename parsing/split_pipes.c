/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:53:13 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:14:42 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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