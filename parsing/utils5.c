/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:29:08 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/06 18:39:09 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_command(t_shell_s *minishell, char *token, int token_num)
{
	if (!minishell || !token)
		return (FALSE);
	if (ft_strncmp(token, ">\0", 2) == 0 || ft_strncmp(token, "<\0", 2) == 0
		|| ft_strncmp(token, "|\0", 2) == 0
		|| ft_strncmp(token, ">>\0", 3) == 0
		|| ft_strncmp(token, "<<\0", 3) == 0)
		return (FALSE);
	if (token_num > 0
		&& (ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				">\0", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				"<\0", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				"<<\0", 3) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[token_num - 1],
				">>\0", 3) == 0))
		return (FALSE);
	return (TRUE);
}

int	get_num_flags(char **token, int i)
{
	t_counter	count;

	if (!token)
		return (0);
	count.counter = 0;
	while (token[i])
	{
		if ((ft_strncmp(token[i], ">\0", 2) == 0
				|| ft_strncmp(token[i], "<\0", 2) == 0
				|| ft_strncmp(token[i], "<<\0", 3) == 0
				|| ft_strncmp(token[i], ">>\0", 3) == 0))
			i++;
		else if (ft_strncmp(token[i], "|\0", 2) != 0)
			count.counter++;
		else if (ft_strncmp(token[i], "|\0", 2) == 0)
			break ;
		i++;
	}
	return (count.counter);
}
		// printf("token num = %i\n", i);
		// printf("token in get_num_flags = %s\n", token[i]);
	// printf("num of args = %i\n", count.counter);

// CASE1: "< |" or "> |"
int	check_validity_case1(t_shell_s *minishell, t_counter *count)
{
	if (minishell->lexer->raw_tokens[count->i + 1]
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
			"|\0", 2) == 0
		&& (ft_strncmp(minishell->lexer->raw_tokens[count->i], ">", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"<", 2) == 0))
		return (TRUE);
	return (FALSE);
}

// CASE2: "< |" or "> |"
int	check_validity_case2(t_shell_s *minishell, t_counter *count)
{
	if ((ft_strncmp(minishell->lexer->raw_tokens[count->i], ">\0", 2) == 0
			|| ft_strncmp(minishell->lexer->raw_tokens[count->i],
				"<\0", 2) == 0)
		&& !minishell->lexer->raw_tokens[count->i + 1])
		return (TRUE);
	return (FALSE);
}

// CASE3: "< |" or "> |"
int	check_validity_case3(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], "<\0", 2) == 0
		&& ((!minishell->lexer->raw_tokens[count->i + 1])
			|| (minishell->lexer->raw_tokens[count->i + 1]
				&& (ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<<\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">>\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"|\0", 2) == 0))))
		return (TRUE);
	return (FALSE);
}

// CASE4: "< |" or "> |"
int	check_validity_case4(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], ">\0", 2) == 0
		&& ((!minishell->lexer->raw_tokens[count->i + 1])
			|| (minishell->lexer->raw_tokens[count->i + 1]
				&& (ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<<\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">>\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"|\0", 2) == 0))))
		return (TRUE);
	return (FALSE);
}

// CASE5: "< |" or "> |"
int	check_validity_case5(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], "<<\0", 3) == 0
		&& ((!minishell->lexer->raw_tokens[count->i + 1])
			|| (minishell->lexer->raw_tokens[count->i + 1]
				&& (ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<<\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">>\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"|\0", 2) == 0))))
		return (TRUE);
	return (FALSE);
}

// CASE6: "< |" or "> |"
int	check_validity_case6(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], ">>\0", 3) == 0
		&& ((!minishell->lexer->raw_tokens[count->i + 1])
			|| (minishell->lexer->raw_tokens[count->i + 1]
				&& (ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">\0", 2) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"<<\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						">>\0", 3) == 0
					|| ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
						"|\0", 2) == 0))))
		return (TRUE);
	return (FALSE);
}

// CASE7: "< |" or "> |"
int	check_validity_case7(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], "|\0", 2) == 0
		&& !minishell->lexer->raw_tokens[count->i + 1])
		return (TRUE);
	return (FALSE);
}

// CASE8: "< |" or "> |"
int	check_validity_case8(t_shell_s *minishell, t_counter *count)
{
	if (ft_strncmp(minishell->lexer->raw_tokens[count->i], "|\0", 2) == 0
		&& ft_strncmp(minishell->lexer->raw_tokens[count->i + 1],
			"|\0", 2) == 0)
		return (TRUE);
	return (FALSE);
}

int	check_validity_all_cases(t_shell_s *minishell, t_counter *count)
{
	if (check_validity_case1(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case2(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case3(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case4(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case5(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case6(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case7(minishell, count) == TRUE)
		return (FALSE);
	if (check_validity_case8(minishell, count) == TRUE)
		return (FALSE);
	return (TRUE);
}

/* CHECK_VALIDITY
- Function to check for syntax error
* CASES
minishell$ < | (Redirection before pipe)
minishell$ > | (Redirection before pipe)
minishell$ < (Redirection with nothing after)
minishell$ | (Pipe with nothing after or before)
minishell$ | | (Pipe with pipe after)
minishell$ < < (Redirection with redirection after)
minishell$ > > (Redirection with redirection after)
minishell$ < > (Redirection with redirection after)
minishell$ > < (Redirection with redirection after)
minishell$ <> (2 redirections in the same token)
minishell$ >< (2 redirections in the same token)
minishell$ cat '<' infile (Not valid redirection if in quotes)
*/
int	check_validity(t_shell_s *minishell, char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (TRUE);
	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens
		|| !minishell->lexer->raw_tokens[0])
		return (FALSE);
	count.i = 0;
	count.j = 0;
	if (minishell->lexer->raw_tokens
		&& ft_strncmp(minishell->lexer->raw_tokens[0], "|\0", 2) == 0)
		return (FALSE);
	while (minishell->lexer->raw_tokens[count.i])
	{
		if (check_validity_all_cases(minishell, &count) == FALSE)
			return (FALSE);
		count.i++;
	}
	return (TRUE);
}
		// if (check_validity_case1(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case2(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case3(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case4(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case5(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case6(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case7(minishell, &count) == TRUE)
		// 	return (FALSE);
		// if (check_validity_case8(minishell, &count) == TRUE)
		// 	return (FALSE);
