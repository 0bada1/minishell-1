/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 17:21:32 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_path(t_shell_s *minishell, char **envp)
{
	t_counter	count;
	char		*temp;

	if (!envp || !envp[0])
		return (minishell->path = NULL, minishell);
	count.i = 0;
	count.j = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "PATH=", 5))
		{
			minishell->path = ft_split(envp[count.i - 1] + 5, ':');
			count.j = 0;
			while (minishell->path[count.j])
			{
				temp = minishell->path[count.j];
				minishell->path[count.j++] = ft_strjoin(temp, "/");
				free(temp);
			}
			break ;
		}
		else if (count.i == ft_strstrlen(envp))
			minishell->path = ft_calloc(1, sizeof(char *));
	}
	return (minishell->path[count.j] = NULL, minishell);
}
				// printf("path[%i] = %s\n", count.j, minishell->path[count.j]);

t_shell_s	*get_env_struct_v1(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i])
	{
		count.j = 0;
		minishell->envp->envp[count.i] = ft_strdup(envp[count.i]);
		minishell->envp->key[count.i] = malloc(sizeof(char)
				* ft_strlen_equals(envp[count.i]) + 1);
		while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
		{
			minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
			count.j++;
		}
		minishell->envp->key[count.i][count.j] = '\0';
		minishell->envp->value[count.i] = ft_strchr(envp[count.i], '=') + 1;
		count.i++;
	}
	minishell->envp->envp[count.i] = NULL;
	minishell->envp->key[count.i] = NULL;
	minishell->envp->value[count.i] = NULL;
	return (minishell);
}

t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	if (!envp || !envp[0])
	{
		minishell->envp = ft_calloc(sizeof(t_env_s), 1);
		minishell->envp->envp = ft_calloc(sizeof(char *), 1);
		minishell->envp->key = ft_calloc(sizeof(char *), 1);
		minishell->envp->value = ft_calloc(sizeof(char *), 1);
		return (minishell->envp->env_size = 0, minishell);
	}
	count.i = 0;
	while (envp[count.i])
		count.i++;
	minishell->envp = ft_calloc(sizeof(t_env_s), 1);
	minishell->envp->env_size = count.i;
	minishell->envp->envp = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell->envp->key = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell->envp->value = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell = get_env_struct_v1(minishell, envp);
	return (minishell->envp->envp[count.i] = NULL, minishell);
}
	// count.i = 0;
	// while (envp[count.i])
	// {
	// 	count.j = 0;
	// 	minishell->envp->envp[count.i] = ft_strdup(envp[count.i]);
	// 	minishell->envp->key[count.i] = malloc(sizeof(char)
	// 			* ft_strlen_equals(envp[count.i]) + 1);
	// 	while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
	// 	{
	// 		minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
	// 		count.j++;
	// 	}
	// 	minishell->envp->key[count.i][count.j] = '\0';
	// 	minishell->envp->value[count.i] = ft_strchr(envp[count.i], '=') + 1;
	// 	count.i++;
	// }
	// minishell->envp->envp[count.i] = NULL;
	// minishell->envp->key[count.i] = NULL;
	// minishell->envp->value[count.i] = NULL;
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
		// minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
		// count.j++;
		// printf("key[%i] = %s\nvalue[%i] = %s\n", count.i,
		// minishell->envp->key[count.i], count.i,
		// minishell->envp->value[count.i]);
	// printf("\n\n\n");
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);

// get_env_struct as linked list
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
// 		// printf("envp[%i] = %s\nkey[%i] = %s\nvalue[%i] = %s\n",
//		count.j, temp->envp, count.j, temp->key, count.j, temp->value);
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

void	get_commands_v1(t_shell_s *minishell, t_counter *count)
{
	if (check_if_command(minishell,
			minishell->lexer->raw_tokens[count->i], count->i) == TRUE)
	{
		minishell->commands[count->j++]
			= ft_strdup(minishell->lexer->tokens[count->i]);
		while (minishell->lexer->tokens[count->i]
			&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"|\0", 2) != 0)
			count->i++;
		if (minishell->lexer->tokens[count->i]
			&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"|\0", 2) == 0)
			count->i++;
	}
	else if (ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
	{
		minishell->commands[count->j] = malloc(sizeof(char) * 1);
		minishell->commands[count->j++][0] = '\0';
		count->i++;
	}
	else
		count->i++;
}

t_shell_s	*get_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	minishell->commands = ft_calloc(sizeof(char *),
			(count_pipes(minishell->cmd_line) + 2));
	while (minishell->lexer->tokens[count.i])
		get_commands_v1(minishell, &count);
	return (minishell->commands[count.j] = NULL, minishell);
}
	// minishell->commands[count.j] = NULL;
	// for (int i = 0; i < minishell->num_commands
	// && minishell->commands[i]; i++)
	// 	printf("command[%i] = %s\n", i, minishell->commands[i]);

void	get_flags_v3(t_shell_s *minishell, t_counter *count)
{
	while (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) != 0)
	{
		if (check_if_command(minishell,
				minishell->lexer->raw_tokens[count->i], count->i) == TRUE)
			minishell->flags[count->j][count->k++]
				= ft_strdup(minishell->lexer->tokens[count->i++]);
		else
			count->i++;
	}
	if (minishell->lexer->raw_tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
		count->i++;
	minishell->flags[count->j++][count->k] = NULL;
}

void	get_flags_v2(t_shell_s *minishell, t_counter *count)
{
	minishell->flags[count->j++][count->k] = NULL;
	while (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) != 0)
		count->i++;
	if (minishell->lexer->tokens[count->i]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i],
			"|\0", 2) == 0)
		count->i++;
}

void	get_flags_v1(t_shell_s *minishell, t_counter *count)
{
	count->k = 0;
	minishell->flags[count->j]
		= ft_calloc(sizeof(char *),
			get_num_flags(minishell->lexer->raw_tokens, count->i) + 1);
	if (get_num_flags(minishell->lexer->raw_tokens, count->i) == 0)
		get_flags_v2(minishell, count);
	else
	{
		get_flags_v3(minishell, count);
	}
}

t_shell_s	*get_flags(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!minishell || !minishell->lexer)
		return (minishell);
	minishell->flags = malloc(sizeof(char **)
			* (count_pipes(minishell->cmd_line) + 2));
	while (minishell->lexer->tokens[count.i])
		get_flags_v1(minishell, &count);
	minishell->flags[count.j] = NULL;
	return (minishell);
}
	// printf("count.j in get_flags = %i && number of commands = %i\n",
	// count.j, count_pipes(minishell->cmd_line) + 1);
	// for (int k = 0; minishell->flags[k]; k++)
	// 	for (int j = 0; minishell->flags[k][j]; j++)
	// 		printf("args[%i][%i] = %s\n", k, j, minishell->flags[k][j]);
// < infile hello "world"| does < infile this work?

t_shell_s	*get_num_commands(t_shell_s *minishell)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	count.counter = 0;
	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens
		|| !minishell->lexer->raw_tokens[0])
		return (NULL);
	while (minishell->lexer->raw_tokens[count.i])
	{
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) != 0)
		{
			while (minishell->lexer->raw_tokens[count.i]
				&& ft_strncmp(minishell->lexer->raw_tokens[count.i],
					"|\0", 2) != 0)
				count.i++;
			count.i--;
			count.counter++;
		}
		count.i++;
	}
	minishell->num_commands = count.counter;
	return (minishell);
}
	// printf("num of commands = %i\n", minishell->num_commands);
//  && minishell->lexer->tokens[count.i + 2]

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

t_shell_s	*get_exec_blocks_v2(t_shell_s *minishell, int i, int z)
{
	minishell->command_block[i] = malloc(sizeof(t_execute) * 1);
	minishell->command_block[i]->num_commands
		= minishell->num_commands;
	minishell->command_block[i]->num_pipes = minishell->num_pipes;
	if (minishell->commands[i])
		minishell->command_block[i]->command
			= ft_strdup(minishell->commands[i]);
	else
		minishell->command_block[i]->command = NULL;
	minishell->command_block[i]->args = malloc(sizeof(char *)
			* (get_num_flags(minishell->lexer->raw_tokens, z) + 1));
	return (minishell);
}

void	get_exec_blocks_v1(t_shell_s *minishell, t_counter *c,
	char **command_block, char **raw_command_block)
{
	c->j = -1;
	minishell = get_exec_blocks_v2(minishell, c->i, c->z);
	command_block = split_command_block(minishell, c->z);
	raw_command_block = split_raw_command_block(minishell, c->z);
	while (minishell->lexer->raw_tokens[c->z]
		&& ft_strncmp(minishell->lexer->raw_tokens[c->z], "|\0", 2) != 0)
		c->z++;
	if (minishell->lexer->raw_tokens[c->z]
		&& ft_strncmp(minishell->lexer->raw_tokens[c->z], "|\0", 2) == 0)
		c->z++;
	if (minishell->flags[c->i])
	{
		while (minishell->flags[c->i][++c->j])
			minishell->command_block[c->i]->args[c->j]
				= ft_strdup(minishell->flags[c->i][c->j]);
	}
	else
		minishell->command_block[c->i]->args[c->j++] = NULL;
	minishell->command_block[c->i]->args[c->j] = NULL;
	minishell->command_block[c->i]
		= get_files(minishell, minishell->command_block[c->i],
			command_block, raw_command_block);
	free_2d(command_block);
	free_2d(raw_command_block);
	minishell->command_block[c->i++]->env = minishell->envp;
}

t_shell_s	*get_execution_blocks(t_shell_s *minishell)
{
	t_counter	c;
	char		**command_block;
	char		**raw_command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens
		|| !minishell->lexer->command_blocks
		|| !minishell->lexer->command_blocks[0])
		return (NULL);
	c.i = 0;
	c.z = 0;
	command_block = NULL;
	raw_command_block = NULL;
	minishell->command_block
		= ft_calloc(sizeof(t_execute *), count_pipes(minishell->cmd_line) + 2);
	while (minishell->lexer->command_blocks[c.i])
		get_exec_blocks_v1(minishell, &c, command_block, raw_command_block);
	return (minishell->command_block[c.i] = NULL, minishell);
}
		// printf("%i\n", get_num_flags(minishell->lexer->tokens, count.z));
	// for (int i = 0; minishell->command_block[i]; i++)
	// 	printf("command[%i] in execution block = %s\n",
	// i, minishell->command_block[i]->command);
	// for (int i = 0; i < minishell->num_commands; i++)
	// 	for (int j = 0; minishell->command_block[i]->args[j]; j++)
	// 		printf("args[%i][%i] in execution blocks = %s\n",
	// i, j, minishell->command_block[i]->args[j]);
		// Num of tokens per command block;
		// minishell->command_block[count.i]->tokens
		// = malloc(sizeof(char *) * ())
			// minishell->command_block[count.i]->tokens[count.j++]
			// = ft_strdup(command_block);
		// minishell->command_block[count.i] = malloc(sizeof(t_execute) * 1);
		// minishell->command_block[count.i]->num_commands
		// 	= minishell->num_commands;
		// minishell->command_block[count.i]->num_pipes = minishell->num_pipes;
		// if (minishell->commands[count.i])
		// 	minishell->command_block[count.i]->command
		// 		= ft_strdup(minishell->commands[count.i]);
		// else
		// 	minishell->command_block[count.i]->command = NULL;
		// minishell->command_block[count.i]->args = malloc(sizeof(char *)
		// 		* (get_num_flags(minishell->lexer->raw_tokens, count.z) + 1));
	// minishell->command_block[count.i] = NULL;
