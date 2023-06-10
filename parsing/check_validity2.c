/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:36:10 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 13:36:20 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
