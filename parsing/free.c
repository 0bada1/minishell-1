/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:35:50 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/24 16:24:54 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    free_everything(t_shell_s *minishell)
{
    t_counter   count;

    count.i = 0;
    count.j = 0;
    count.k = 0;
	count.m = 0;
    count.n = 0;
	if (!minishell)
		return ;
    if (minishell->cmd_line != NULL)
	{
        free(minishell->cmd_line);
		minishell->cmd_line = NULL;
	}
    free_2d(minishell->commands);
    // for (int i = 0; minishell->path[i]; i++)
    //     printf("%s\n", minishell->path[i]);
    free_2d(minishell->path);
    // if (!minishell->path)
        // printf("No path\n");
    // if (minishell->commands != NULL)
    // {
    //     while (minishell->commands[count.i])
    //         free(minishell->commands[count.i++]);
    //     free(minishell->commands);
    // }
    // if (minishell->path != NULL)
    // {
    //     while (minishell->path[count.j])
    //         free(minishell->path[count.j++]);
    //     free(minishell->path);
    // }
    if (minishell->lexer != NULL)
    {
        free_2d(minishell->lexer->tokens);
        free_2d(minishell->lexer->raw_tokens);
        free_2d(minishell->lexer->command_blocks);
        // if (minishell->lexer->tokens != NULL)
        // {
        //     while (minishell->lexer->tokens[count.k])
        //         free(minishell->lexer->tokens[count.k++]);
        //     free(minishell->lexer->tokens);
        // }
        free(minishell->lexer);
    }
    // free_3d(minishell->flags);
    if (minishell->command_block)
    {
        while (minishell->command_block[count.n])
        {
            if (minishell->command_block[count.n]->command)
                free(minishell->command_block[count.n]->command);
            free_2d(minishell->command_block[count.n]->args);
            // free_2d(minishell->command_block[count.n]->tokens);
            if (minishell->command_block[count.n]->files)
            {
                if (minishell->command_block[count.n]->files->redirect_type)
                    free(minishell->command_block[count.n]->files->redirect_type);
                free_2d(minishell->command_block[count.n]->files->infile_name);
                free_2d(minishell->command_block[count.n]->files->outfile_name);
                free_2d(minishell->command_block[count.n]->files->append_name);
                free_2d(minishell->command_block[count.n]->files->limiter);
                free(minishell->command_block[count.n]->files);
            }
            free(minishell->command_block[count.n++]);
        }
        free(minishell->command_block);
    }
    if (minishell->envp)
    {
        free_2d(minishell->envp->envp);
        free_2d(minishell->envp->key);
        // free_2d(minishell->envp->value);
        free(minishell->envp);
    }
	if (minishell->flags != NULL)
	{
		while (minishell->flags[count.m])
		{
			count.n = 0;
			while (minishell->flags[count.m][count.n])
				free(minishell->flags[count.m][count.n++]);
			free(minishell->flags[count.m++]);
		}
		free(minishell->flags);
	}
	// free_2d(minishell->command_block);
    if (minishell != NULL)
        free(minishell);
}

void    free_after_execution(t_shell_s *minishell)
{
    t_counter   count;

    if (!minishell)
        return ;
    free_3d(minishell->flags);
    free_2d(minishell->commands);
    if (minishell->cmd_line)
        free(minishell->cmd_line);
    if (minishell->lexer)
    {
        free_2d(minishell->lexer->command_blocks);
        free_2d(minishell->lexer->raw_tokens);
        free_2d(minishell->lexer->tokens);
        free(minishell->lexer);
    }
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
    if (minishell->command_block)
    {
        count.i = 0;
        while (minishell->command_block[count.i])
        {
            if (minishell->command_block[count.i]->command)
                free(minishell->command_block[count.i]->command);
            free_2d(minishell->command_block[count.i]->args);
            // for (int i = 0; minishell->command_block[count.i]->tokens[i]; i++)
            //     printf("%s\n", minishell->command_block[count.i]->tokens[i]);
            // free_2d(minishell->command_block[count.i]->tokens);
            if (minishell->command_block[count.i]->files)
            {
                free_2d(minishell->command_block[count.i]->files->infile_name);
                free_2d(minishell->command_block[count.i]->files->outfile_name);
                free_2d(minishell->command_block[count.i]->files->append_name);
                free_2d(minishell->command_block[count.i]->files->limiter);
                if (minishell->command_block[count.i]->files->redirect_type)
                    free(minishell->command_block[count.i]->files->redirect_type);
                free(minishell->command_block[count.i]->files);
            }
            free(minishell->command_block[count.i]);
            count.i++;
        }
        free(minishell->command_block);
    }
    return ;
}

void    free_2d(char **array)
{
    int i;

    if (!array)
        return ;
    if (!array[0])
    {
        free(array);
        return ;
    }
    i = 0;
    if (array != NULL)
    {
        if (array[i])
        {
            while (array[i])
            {
                if (array[i] != NULL)
                    free(array[i++]);
            }
        }
        free(array);
        array = NULL;
    }
    return ;
}

void	free_3d(char ***array)
{
	int	i;
	int	j;

    if (!array)
        return ;
    if (!array[0])
    {
        free(array);
        return ;
    }
	i = 0;
	j = 0;
	if (array)
	{
		while (array[i])
		{
            if (array[i][j])
            {

            }
			while (array[i][j])
			{
				if (array[i][j] != NULL)
					free(array[i][j++]);
			}
                free(array[i++]);
		}
		free(array);
        array = NULL;
	}
}