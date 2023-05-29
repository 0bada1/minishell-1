/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/27 17:07:10 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_path(t_shell_s *minishell, char **envp)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!envp)
		return (minishell->path = NULL, minishell);
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "PATH=", 5))
		{
			minishell->path = ft_split(envp[count.i - 1] + 5, ':');
			count.j = 0;
			while (minishell->path[count.j])
			{
				char *temp = minishell->path[count.j];
				minishell->path[count.j] = ft_strjoin(temp, "/");
				free(temp);
				// printf("path[%i] = %s\n", count.j, minishell->path[count.j]);
				count.j++;
			}
			break ;
		}
	}
	minishell->path[count.j] = NULL;
	return (minishell);
}

t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	count.i = 0;
	while (envp[count.i])
		count.i++;
	minishell->envp = ft_calloc(sizeof(t_env_s), 1);
	minishell->envp->env_size = count.i;
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
	minishell->envp->envp = ft_calloc(sizeof(char *), minishell->envp->env_size + 1);
	minishell->envp->key = ft_calloc(sizeof(char *), minishell->envp->env_size + 1);
	minishell->envp->value = ft_calloc(sizeof(char *), minishell->envp->env_size + 1);
	count.i = 0;
	while (envp[count.i])
	{
		count.j = 0;
		minishell->envp->envp[count.i] = ft_strdup(envp[count.i]);
		minishell->envp->key[count.i] = malloc(sizeof(char) * ft_strlen_equals(envp[count.i]) + 1);
		while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
		{
			minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
			count.j++;
		}
		minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
		count.j++;
		minishell->envp->key[count.i][count.j] = '\0';
		minishell->envp->value[count.i] = ft_strchr(envp[count.i], '=') + 1;
		// printf("key[%i] = %s\nvalue[%i] = %s\n", count.i, minishell->envp->key[count.i], count.i, minishell->envp->value[count.i]);
		count.i++;
	}
	// printf("\n\n\n");
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
	minishell->envp->envp[count.i] = NULL;
	minishell->envp->key[count.i] = NULL;
	minishell->envp->value[count.i] = NULL;
	return (minishell);
}

// t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
// {
// 	t_env_s		*temp;
// 	t_counter	count;

// 	if (!minishell)
// 		return (NULL);
// 	if (!envp)
// 		return (minishell);
// 	count.i = 0;
// 	while (envp[count.i])
// 		count.i++;
// 	minishell->envp = ft_calloc(sizeof(t_env_s), 1);
// 	temp = minishell->envp;
// 	// printf("count.i in envp function = %i\n\n", count.i);
// 	count.j = 0;
// 	while (count.j < count.i)
// 	{
// 		count.k = 0;
// 		temp->env_size = count.i;
// 		temp->envp = ft_strdup(envp[count.j]);
// 		temp->key = malloc(sizeof(char) * ft_strlen_equals(envp[count.j]) + 1);
// 		while (envp[count.j][count.k] && envp[count.j][count.k] != '=')
// 		{
// 			temp->key[count.k] = envp[count.j][count.k];
// 			count.k++;
// 		}
// 		temp->key[count.k] = '=';
// 		count.k++;
// 		temp->key[count.k] = '\0';
// 		temp->value = ft_strchr(envp[count.j], '=') + 1;
// 		// printf("envp[%i] = %s\nkey[%i] = %s\nvalue[%i] = %s\n", count.j, temp->envp, count.j, temp->key, count.j, temp->value);
// 		if (count.j + 1 < minishell->envp->env_size)
// 		{
// 			temp->next = ft_calloc(sizeof(t_env_s), 1);
// 			temp = temp->next;
// 		}
// 		else
// 			temp->next = NULL;
// 		count.j++;
// 	}
// 	return (minishell);
// }

t_shell_s	*get_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	minishell->commands = ft_calloc(sizeof(char *), (count_pipes(minishell->cmd_line) + 2));
	// minishell->flags = malloc(sizeof(char **) * (minishell->num_commands + 1));
	while (minishell->lexer->tokens[count.i])
	{
		if (check_if_command(minishell, minishell->lexer->raw_tokens[count.i], count.i) == TRUE)
		{
			// printf("token = %s\n", minishell->lexer->raw_tokens[count.i]);
			// char * temp = minishell->commands[count.j];
			minishell->commands[count.j++] = ft_strdup(minishell->lexer->tokens[count.i]);
			// free(temp);
			while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
				count.i++;
			if (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0)
				count.i++;
			// minishell->flags[count.j] = ft_calloc(sizeof(char *), get_num_flags(minishell->lexer->raw_tokens, count.m) + 1);
			// while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
			// 	minishell->flags[count.j][count.k++] = ft_strdup(minishell->lexer->tokens[count.i++]);
			// minishell->flags[count.j++][count.k] = NULL;
			// count.m = count.i;
		}
		else if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0)
		{
			// printf("count.j = %i\n", count.j);
			minishell->commands[count.j] = malloc(sizeof(char) * 1);
			minishell->commands[count.j++][0] = '\0';
			count.i++;
		}
		else
			count.i++;
		// printf("%s\n", minishell->lexer->raw_tokens[count.i]);
		// while (minishell->lexer->raw_tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
		// 	count.i++;
		// if (minishell->lexer->raw_tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0)
		// 	count.i++;
	}
	minishell->commands[count.j] = NULL;
	// for (int i = 0; i < minishell->num_commands && minishell->commands[i]; i++)
	// 	printf("command[%i] = %s\n", i, minishell->commands[i]);
	// for (int k = 0; k < minishell->num_commands; k++)
	// 	for (int j = 0; j < get_num_flags(minishell->lexer->tokens, k); j++)
	// 		printf("args[%i] = %s\n", j, minishell->flags[k][j]);
	return (minishell);
}

t_shell_s	*get_flags(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	// minishell->flags = malloc(sizeof(char **) * (minishell->num_commands + 1));
	minishell->flags = malloc(sizeof(char **) * (count_pipes(minishell->cmd_line) + 2));
	while (minishell->lexer->tokens[count.i])
	{
		count.k = 0;
		minishell->flags[count.j] = ft_calloc(sizeof(char *), get_num_flags(minishell->lexer->raw_tokens, count.i) + 1);
		if (get_num_flags(minishell->lexer->raw_tokens, count.i) == 0)
		{
			minishell->flags[count.j++][count.k] = NULL;
			while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
				count.i++;
			if (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0)
				count.i++;
		}
		else
		{
			while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
			{
				if (check_if_command(minishell, minishell->lexer->raw_tokens[count.i], count.i) == TRUE)
					minishell->flags[count.j][count.k++] = ft_strdup(minishell->lexer->tokens[count.i++]);
				else
					count.i++;
			}
			if (minishell->lexer->raw_tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0)
				count.i++;
			minishell->flags[count.j++][count.k] = NULL;
		}
	}
	// printf("count.j in get_flags = %i && number of commands = %i\n", count.j, count_pipes(minishell->cmd_line) + 1);
	minishell->flags[count.j] = NULL;
	// for (int k = 0; minishell->flags[k]; k++)
	// 	for (int j = 0; minishell->flags[k][j]; j++)
	// 		printf("args[%i][%i] = %s\n", k, j, minishell->flags[k][j]);
	return (minishell);
}
// < infile hello "world"| does < infile this work?

t_shell_s	*get_num_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	count.counter = 0;
	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens || !minishell->lexer->raw_tokens[0])
		return (NULL);
	// printf("token[0] in get num cmds = %s\n", minishell->lexer->tokens[count.i]);
	while (minishell->lexer->raw_tokens[count.i])
	{
		// if (count.i > 0 && (ft_strncmp(minishell->lexer->raw_tokens[count.i - 1], ">\0", 2) == 0 || ft_strncmp(minishell->lexer->raw_tokens[count.i - 1], "<\0", 2) == 0))
		// 	count.i++;
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
		{
			while (minishell->lexer->raw_tokens[count.i] && ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
				count.i++;
			count.i--;
			count.counter++;
		}
		count.i++;
		// printf("count.i = %i\n", count.i);
		// printf("i in get_num_commands = %i\n", count.i);
	}
	minishell->num_commands = count.counter;
	// printf("num of commands = %i\n", minishell->num_commands);
	// printf("number of commands = %i\n", minishell->num_commands);
	return (minishell);
}
//  && minishell->lexer->tokens[count.i + 2]

// Gets t_files for the t_execution command_block
t_execute	*get_files(t_shell_s *minishell, t_execute *execute_block, char **command_block, char **raw_command_block)
{
	t_counter	count;

	if (!minishell || !execute_block)
		return (NULL);
	if (!minishell->lexer || !minishell->lexer->raw_tokens || !command_block)
		return (execute_block);
	count.i = 0;
	count.j = 0;
	count.k = 0;
	count.m = 0;
	count.n = 0;
	count.counter = 0;
	execute_block->files = ft_calloc(sizeof(t_files), 1);
	execute_block->files->infile_name = malloc(sizeof(char *) * (count_infiles(raw_command_block) + 1));
	execute_block->files->outfile_name = malloc(sizeof(char *) * (count_outfiles(raw_command_block) + 1));
	execute_block->files->append_name = malloc(sizeof(char *) * (count_appends(raw_command_block) + 1));
	execute_block->files->limiter = malloc(sizeof(char *) * (count_heredocs(raw_command_block) + 1));
	execute_block->files->redirect_type = malloc(sizeof(char) * (count_appends(raw_command_block) + count_heredocs(raw_command_block) + count_infiles(raw_command_block) + count_outfiles(raw_command_block) + 1));
	// printf("number of infiles = %i\n", count_infiles(command_block));
	while (command_block[count.i])
	{
		// printf("command_block[%i] in get_files = %s\n", count.i, command_block[count.i]);
		if (ft_strncmp(raw_command_block[count.i], ">>\0", 3) == 0)
		{
			execute_block->files->redirect_type[count.counter++] = 'a';
			execute_block->files->append_name[count.m++] = ft_strdup(command_block[count.i + 1]);
			count.i += 2;
		}
		else if (ft_strncmp(raw_command_block[count.i], "<<\0", 3) == 0)
		{
			execute_block->files->redirect_type[count.counter++] = 'h';
			execute_block->files->limiter[count.n++] = ft_strdup(command_block[count.i + 1]);
			count.i += 2;
		}
		else if (ft_strncmp(raw_command_block[count.i], "<\0", 2) == 0)
		{
			execute_block->files->redirect_type[count.counter++] = '<';
			// printf("count.i = %i && file = %s\n", count.i, command_block[count.i + 1]);
			execute_block->files->infile_name[count.j++] = ft_strdup(command_block[count.i + 1]);
			count.i += 2;
		}
		else if (ft_strncmp(raw_command_block[count.i], ">\0", 2) == 0)
		{
			execute_block->files->redirect_type[count.counter++] = '>';
			execute_block->files->outfile_name[count.k++] = ft_strdup(command_block[count.i + 1]);
			count.i += 2;
		}
		else
			count.i++;
	}
	execute_block->files->infile_name[count.j] = NULL;
	execute_block->files->outfile_name[count.k] = NULL;
	execute_block->files->append_name[count.m] = NULL;
	execute_block->files->limiter[count.n] = NULL;
	execute_block->files->redirect_type[count.counter] = '\0';
	execute_block->files->num_of_redirections = count.counter;
	return (execute_block);
}
	// for (int i = 0; execute_block->files->infile_name[i]; i++)
	// 	printf("infile[%i] = %s\n", i, execute_block->files->infile_name[i]);
	// for (int i = 0; execute_block->files->outfile_name[i]; i++)
	// 	printf("outfile[%i] = %s\n", i, execute_block->files->outfile_name[i]);
	// for (int i = 0; execute_block->files->append_name[i]; i++)
	// 	printf("append[%i] = %s\n", i, execute_block->files->append_name[i]);
	// for (int i = 0; execute_block->files->limiter[i]; i++)
	// 	printf("limiter[%i] = %s\n", i, execute_block->files->limiter[i]);
	// printf("files order = %s\n", execute_block->files->redirect_type);

t_shell_s	*get_execution_blocks(t_shell_s *minishell)
{
	t_counter	count;
	char		**command_block;
	char		**raw_command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens || !minishell->lexer->command_blocks || !minishell->lexer->command_blocks[0])
		return (NULL);
	count.i = 0;
	count.z = 0;
	minishell->command_block = ft_calloc(sizeof(t_execute *), count_pipes(minishell->cmd_line) + 2);
	while (minishell->lexer->command_blocks[count.i])
	{
		count.j = 0;
		minishell->command_block[count.i] = malloc(sizeof(t_execute) * 1);
		minishell->command_block[count.i]->num_commands = minishell->num_commands;
		minishell->command_block[count.i]->num_pipes = minishell->num_pipes;
		if (minishell->commands[count.i])
			minishell->command_block[count.i]->command = ft_strdup(minishell->commands[count.i]);
		else
			minishell->command_block[count.i]->command = NULL;
		minishell->command_block[count.i]->args = malloc(sizeof(char *) * (get_num_flags(minishell->lexer->raw_tokens, count.z) + 1));
		command_block = split_command_block(minishell, count.z);
		raw_command_block = split_raw_command_block(minishell, count.z);
		// Num of tokens per command block;
		// minishell->command_block[count.i]->tokens = malloc(sizeof(char *) * ())
		while (minishell->lexer->raw_tokens[count.z] && ft_strncmp(minishell->lexer->raw_tokens[count.z], "|\0", 2) != 0)
		{
			// minishell->command_block[count.i]->tokens[count.j++] = ft_strdup(command_block);
			count.z++;
		}
		count.j = 0;
		if (minishell->lexer->raw_tokens[count.z] && ft_strncmp(minishell->lexer->raw_tokens[count.z], "|\0", 2) == 0)
			count.z++;
		if (minishell->flags[count.i])
		{
			while (minishell->flags[count.i][count.j])
			{
				minishell->command_block[count.i]->args[count.j] = ft_strdup(minishell->flags[count.i][count.j]);
				count.j++;
			}
		}
		else
			minishell->command_block[count.i]->args[count.j++] = NULL;
		minishell->command_block[count.i]->args[count.j] = NULL;
		minishell->command_block[count.i] = get_files(minishell, minishell->command_block[count.i], command_block, raw_command_block);
		free_2d(command_block);
		free_2d(raw_command_block);
		minishell->command_block[count.i]->env = minishell->envp;
		count.i++;
	}
	minishell->command_block[count.i] = NULL;
	return (minishell);
}
		// printf("%i\n", get_num_flags(minishell->lexer->tokens, count.z));
	// for (int i = 0; minishell->command_block[i]; i++)
	// 	printf("command[%i] in execution block = %s\n", i, minishell->command_block[i]->command);
	// for (int i = 0; i < minishell->num_commands; i++)
	// 	for (int j = 0; minishell->command_block[i]->args[j]; j++)
	// 		printf("args[%i][%i] in execution blocks = %s\n", i, j, minishell->command_block[i]->args[j]);