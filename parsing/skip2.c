/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:22:36 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:24:14 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
