/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:20:46 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 16:20:59 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_everything_utils3(t_shell_s *minishell)
{
	if (minishell->pipes_fd)
		free(minishell->pipes_fd);
	if (minishell->pid)
		free(minishell->pid);
	if (minishell != NULL)
		free(minishell);
}

void	free_everything_utils2(t_shell_s *minishell)
{
	t_counter	c;

	c.n = 0;
	if (minishell->command_block)
	{
		while (minishell->command_block[c.n])
		{
			if (minishell->command_block[c.n]->command)
				free(minishell->command_block[c.n]->command);
			free_2d(minishell->command_block[c.n]->args);
			if (minishell->command_block[c.n]->files)
			{
				if (minishell->command_block[c.n]->files->redirect_type)
					free(minishell->command_block[c.n]->files->redirect_type);
				free_2d(minishell->command_block[c.n]->files->infile_name);
				free_2d(minishell->command_block[c.n]->files->outfile_name);
				free_2d(minishell->command_block[c.n]->files->append_name);
				free_2d(minishell->command_block[c.n]->files->limiter);
				free(minishell->command_block[c.n]->files);
			}
			free(minishell->command_block[c.n++]);
		}
		free(minishell->command_block);
	}
	free_everything_utils3(minishell);
}

void	free_everything_utils(t_shell_s *minishell)
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
	if (minishell->envp)
	{
		free_2d(minishell->envp->envp);
		free_2d(minishell->envp->key);
		free(minishell->envp->value);
		free_2d(minishell->envp->export_key);
		free_2d(minishell->envp->export_value);
		free_2d(minishell->envp->export_env);
		free(minishell->envp);
	}
	free_everything_utils2(minishell);
}

void	free_everything(t_shell_s *minishell)
{
	if (!minishell)
		return ;
	if (minishell->cmd_line != NULL)
	{
		free(minishell->cmd_line);
		minishell->cmd_line = NULL;
	}
	free_2d(minishell->commands);
	free_2d(minishell->path);
	if (minishell->lexer != NULL)
	{
		free_2d(minishell->lexer->tokens);
		free_2d(minishell->lexer->raw_tokens);
		free_2d(minishell->lexer->command_blocks);
		free(minishell->lexer);
	}
	free_3d(minishell->flags);
	free_everything_utils(minishell);
}
