/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:16:14 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 19:16:21 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_files_outfile_condition(t_execute *execute_block,
	char **command_block, t_counter *count)
{
	execute_block->files->redirect_type[count->counter++] = '>';
	if (command_block[count->i + 1])
		execute_block->files->outfile_name[count->k++]
			= ft_strdup(command_block[count->i + 1]);
	else
		execute_block->files->outfile_name[count->k++] = NULL;
	count->i += 2;
}

void	get_files_malloc_names(t_execute *execute_block,
	char **raw_command_block)
{
	execute_block->files = ft_calloc(sizeof(t_files), 1);
	execute_block->files->infile_name = malloc(sizeof(char *)
			* (count_infiles(raw_command_block) + 1));
	execute_block->files->outfile_name = malloc(sizeof(char *)
			* (count_outfiles(raw_command_block) + 1));
	execute_block->files->append_name = malloc(sizeof(char *)
			* (count_appends(raw_command_block) + 1));
	execute_block->files->limiter = malloc(sizeof(char *)
			* (count_heredocs(raw_command_block) + 1));
	execute_block->files->redirect_type = malloc(sizeof(char)
			* (count_appends(raw_command_block)
				+ count_heredocs(raw_command_block)
				+ count_infiles(raw_command_block)
				+ count_outfiles(raw_command_block) + 1));
}

void	get_files_initialize_counters(t_counter *count)
{
	count->i = 0;
	count->j = 0;
	count->k = 0;
	count->m = 0;
	count->n = 0;
	count->counter = 0;
}

void	get_files_nullify_vars(t_execute *execute_block, t_counter *count)
{
	execute_block->files->infile_name[count->j] = NULL;
	execute_block->files->outfile_name[count->k] = NULL;
	execute_block->files->append_name[count->m] = NULL;
	execute_block->files->limiter[count->n] = NULL;
	execute_block->files->redirect_type[count->counter] = '\0';
}

// Gets t_files for the t_execution command_block
t_execute	*get_files(t_shell_s *minishell, t_execute *execute_block,
	char **command_block, char **raw_command_block)
{
	t_counter	count;

	if (!minishell || !execute_block)
		return (NULL);
	if (!minishell->lexer || !minishell->lexer->raw_tokens || !command_block)
		return (execute_block);
	get_files_initialize_counters(&count);
	get_files_malloc_names(execute_block, raw_command_block);
	while (command_block[count.i])
	{
		if (ft_strncmp(raw_command_block[count.i], ">>\0", 3) == 0)
			get_files_append_condition(execute_block, command_block, &count);
		else if (ft_strncmp(raw_command_block[count.i], "<<\0", 3) == 0)
			get_files_heredoc_condition(execute_block, command_block, &count);
		else if (ft_strncmp(raw_command_block[count.i], "<\0", 2) == 0)
			get_files_infile_condition(execute_block, command_block, &count);
		else if (ft_strncmp(raw_command_block[count.i], ">\0", 2) == 0)
			get_files_outfile_condition(execute_block, command_block, &count);
		else
			count.i++;
	}
	get_files_nullify_vars(execute_block, &count);
	execute_block->files->num_of_redirections = count.counter;
	return (execute_block);
}
		// printf("command_block[%i] in get_files = %s\n",
		// count.i, command_block[count.i]);
	// for (int i = 0; execute_block->files->infile_name[i]; i++)
	// 	printf("infile[%i] = %s\n", i, execute_block->files->infile_name[i]);
	// for (int i = 0; execute_block->files->outfile_name[i]; i++)
	// 	printf("outfile[%i] = %s\n", i, execute_block->files->outfile_name[i]);
	// for (int i = 0; execute_block->files->append_name[i]; i++)
	// 	printf("append[%i] = %s\n", i, execute_block->files->append_name[i]);
	// for (int i = 0; execute_block->files->limiter[i]; i++)
	// 	printf("limiter[%i] = %s\n", i, execute_block->files->limiter[i]);
	// printf("files order = %s\n", execute_block->files->redirect_type);
