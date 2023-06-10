/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_after_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:21:06 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 21:13:01 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_after_execution_utils2(t_shell_s *minishell)
{
	if (minishell->files)
	{
		free_2d(minishell->files->infile_name);
		free_2d(minishell->files->outfile_name);
		free_2d(minishell->files->append_name);
		free_2d(minishell->files->limiter);
		if (minishell->files->redirect_type)
			free(minishell->files->redirect_type);
		free(minishell->files);
	}
	if (minishell->pipes_fd)
		free(minishell->pipes_fd);
	if (minishell->pid)
		free(minishell->pid);
}

void	free_after_execution_utils(t_shell_s *minishell)
{
	t_counter	c;

	if (minishell->command_block)
	{
		c.i = 0;
		while (minishell->command_block[c.i])
		{
			if (minishell->command_block[c.i]->command)
				free(minishell->command_block[c.i]->command);
			free_2d(minishell->command_block[c.i]->args);
			if (minishell->command_block[c.i]->files)
			{
				free_2d(minishell->command_block[c.i]->files->infile_name);
				free_2d(minishell->command_block[c.i]->files->outfile_name);
				free_2d(minishell->command_block[c.i]->files->append_name);
				free_2d(minishell->command_block[c.i]->files->limiter);
				if (minishell->command_block[c.i]->files->redirect_type)
					free(minishell->command_block[c.i]->files->redirect_type);
				free(minishell->command_block[c.i]->files);
			}
			free(minishell->command_block[c.i++]);
		}
		free(minishell->command_block);
	}
	free_after_execution_utils2(minishell);
}

void	free_after_execution(t_shell_s *minishell)
{
	if (!minishell)
		return ;
	free_3d(minishell->flags);
	free_2d(minishell->commands);
	if (minishell->cmd_line)
	{
		free(minishell->cmd_line);
		minishell->cmd_line = 0;
	}
	if (minishell->lexer)
	{
		free_2d(minishell->lexer->command_blocks);
		free_2d(minishell->lexer->raw_tokens);
		free_2d(minishell->lexer->tokens);
		free(minishell->lexer);
	}
	free_after_execution_utils(minishell);
}
