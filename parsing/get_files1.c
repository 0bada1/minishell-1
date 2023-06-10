/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:24:41 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:16:10 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_files_append_condition(t_execute *execute_block,
	char **command_block, t_counter *count)
{
	execute_block->files->redirect_type[count->counter++] = 'a';
	if (command_block[count->i + 1])
		execute_block->files->append_name[count->m++]
			= ft_strdup(command_block[count->i + 1]);
	else
		execute_block->files->append_name[count->m++] = NULL;
	count->i += 2;
}

void	get_files_heredoc_condition(t_execute *execute_block,
	char **command_block, t_counter *count)
{
	execute_block->files->redirect_type[count->counter++] = 'h';
	if (command_block[count->i + 1])
		execute_block->files->limiter[count->n++]
			= ft_strdup(command_block[count->i + 1]);
	else
		execute_block->files->limiter[count->n++] = NULL;
	count->i += 2;
}

void	get_files_infile_condition(t_execute *execute_block,
	char **command_block, t_counter *count)
{
	execute_block->files->redirect_type[count->counter++] = '<';
	if (command_block[count->i + 1])
		execute_block->files->infile_name[count->j++]
			= ft_strdup(command_block[count->i + 1]);
	else
		execute_block->files->infile_name[count->j++] = NULL;
	count->i += 2;
}
