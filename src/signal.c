/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:17:15 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/07 16:23:50 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

/*
is used to insert a newline character ("\n") into the input buffer of the
terminal associated with the standard input file descriptor (STDIN_FILENO).

The TIOCSTI control operation, which stands for Terminal Input Output
Control STack Insert, is used to insert characters into the terminal input
buffer. By invoking this operation, you can simulate the effect of typing 
a specific character or sequence of characters as input.
*/
void	ft_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
