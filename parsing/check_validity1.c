/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:34:56 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 16:44:56 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (minishell->lexer = NULL, FALSE);
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
