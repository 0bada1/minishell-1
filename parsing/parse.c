/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:43 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 14:23:45 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

t_shell_s	*parse_cmds(t_shell_s *minishell, char *str)
{
	if (minishell)
		minishell->num_pipes = count_pipes(str);
	minishell = get_num_commands(minishell);
	minishell = get_commands(minishell);
	minishell = get_flags(minishell);
	minishell = get_execution_blocks(minishell);
	return (minishell);
}

t_shell_s	*parse_fds(t_shell_s *minishell, int iteration)
{
	if (!minishell)
		return (NULL);
	if (iteration == 0)
	{
		minishell->std_in = dup(STDIN_FILENO);
		minishell->std_out = dup(STDOUT_FILENO);
	}
	minishell->pid = 0;
	minishell->pipes_fd = 0;
	minishell->cmd_used = -1;
	return (minishell);
}

// Parse dollar sign and lexer
t_shell_s	*parse_dsl(t_shell_s *minishell, char *str, int num, char **envp)
{
	char		*expanded_str;

	expanded_str = dollar_sign(minishell, str);
	if (minishell)
		minishell->cmd_line = ft_strdup(str);
	if (num == 0)
	{
		minishell = get_path(minishell, envp);
		minishell = get_env_struct(minishell, envp);
	}
	minishell = lexer(minishell, expanded_str);
	minishell = raw_lexer(minishell, str);
	if (minishell && minishell->lexer)
		minishell->lexer->num_of_tokens = num_of_tokens(expanded_str);
	free(expanded_str);
	if (minishell && minishell->lexer)
		minishell->lexer->command_blocks = split_pipes(str);
	return (minishell);
}

t_shell_s	*parse(t_shell_s *minishell, char *str, char **envp, int iteration)
{
	minishell = parse_fds(minishell, iteration);
	if (number_of_dquotes(str) % 2 == 1 || number_of_squotes(str) % 2 == 1)
	{
		ft_putstr_fd("Minishell: Error: lexer: Odd number of quotes\n",
			STDERR_FILENO);
		g_exit_code = 1;
		return (minishell);
	}
	minishell = parse_dsl(minishell, str, iteration, envp);
	if (check_validity(minishell, str) == FALSE)
	{
		free_after_execution(minishell);
		ft_putstr_fd("Error: Syntax\n", STDERR_FILENO);
		g_exit_code = 2;
		return (minishell);
	}
	return (minishell = parse_cmds(minishell, str), minishell);
}
	// if (iteration == 0)
	// {
	// 	minishell->std_in = dup(STDIN_FILENO);
	// 	minishell->std_out = dup(STDOUT_FILENO);
	// }
	// minishell->pid = 0;
	// minishell->pipes_fd = 0;
	// minishell->cmd_used = -1;
	// expanded_str = dollar_sign(minishell, str);
	// minishell->cmd_line = ft_strdup(str);
	// if (iteration == 0)
	// {
	// 	minishell = get_path(minishell, envp);
	// 	minishell = get_env_struct(minishell, envp);
	// }
	// minishell = lexer(minishell, expanded_str);
	// minishell = raw_lexer(minishell, str);
	// minishell->lexer->num_of_tokens = num_of_tokens(expanded_str);
	// free(expanded_str);
	// if (minishell && minishell->lexer)
	// 	minishell->lexer->command_blocks = split_pipes(str);
	// if (minishell)
	// 	minishell->num_pipes = count_pipes(str);
	// minishell = get_num_commands(minishell);
	// minishell = get_commands(minishell);
	// minishell = get_flags(minishell);
	// minishell = get_execution_blocks(minishell);
