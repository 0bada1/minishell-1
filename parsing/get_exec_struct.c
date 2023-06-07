/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:23:32 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:20:26 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_heredoc_append(char *str, t_counter *c)
{
	if ((str[c->i] == '>'
			&& str[c->i + 1] && str[c->i + 1] == '>')
		|| (str[c->i] == '<'
			&& str[c->i + 1] && str[c->i + 1] == '<'))
		return (TRUE);
	return (FALSE);
}

int	is_infile_outfile_pipe(char *str, t_counter *c)
{
	if (str[c->i] == '>' || str[c->i] == '<' || str[c->i] == '|')
		return (TRUE);
	return (FALSE);
}

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