/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:15:26 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/06 23:28:21 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_code;

/*
for arg it should be numaric between ULLi 9223372036854775807
and -9223372036854775808
++ or -- not allowed (only one)
*/

unsigned long long int	ft_my_attoi(char *str, int *s)
{
	unsigned long long	r;
	char				*tmp;

	tmp = str;
	*s = 1;
	r = 0;
	if (*str == '-')
		*s = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		r = r * 10 + (*str++ - '0');
	if (*s == -1 && r == 9223372036854775807)
		return (2);
	if (!ft_strncmp("-9223372036854775808", tmp, 20))
		return (3);
	if (*s == -1 && r > 9223372036854775807)
		return (1);
	if (*s == 1 && r > 9223372036854775807)
		return (1);
	return (r);
}

void	exit_ok(unsigned long long int num, int *s, t_shell_s *shell)
{
	int	r;

	r = 0;
	if (*s == 1 && num >= 256)
		r = num % 256;
	else if (*s == -1)
	{
		if (num > 256)
			r = num % 256;
		else
			r = 256 - num;
	}
	else
		r = num;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit_code = r;
	close_all_fd();
	free_everything(shell);
	exit(g_exit_code);
}

int	check_exit_args(char *str, int *s)
{
	int	i;

	i = 0;
	if (!str[i] || (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-'))
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1 || i > 20)
			return (1);
		i++;
	}
	if (ft_my_attoi(str, s) == 1 && i > 3)
		return (1);
	if (ft_my_attoi(str, s) == 2 && i > 3)
		return (2);
	if (ft_my_attoi(str, s) == 3 && i > 3)
		return (3);
	return (0);
}

void	exit_status(char *str, int code, int fd, t_shell_s *shell)
{
	ft_putstr_fd(str, fd);
	free_error(shell);
	exit(code);
}

void	ft_exit(t_execute *exec, t_shell_s *shell)
{
	int	s;

	if (!exec->args[1])
		exit_status("exit\n", g_exit_code, STDOUT_FILENO, shell);
	else if (exec->args[2])
		exit_status("exit\nminishell: exit: too many arguments\n",
			EXIT_FAILURE, STDERR_FILENO, shell);
	else if (exec->args[1] && !check_exit_args(exec->args[1], &s))
		exit_ok(ft_my_attoi(exec->args[1], &s), &s, shell);
	else if (exec->args[1] && check_exit_args(exec->args[1], &s) == 2)
		exit_status("exit\n", EXIT_FAILURE, STDOUT_FILENO, shell);
	else if (exec->args[1] && check_exit_args(exec->args[1], &s) == 3)
		exit_status("exit\n", EXIT_SUCCESS, STDOUT_FILENO, shell);
	else
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(exec->args[1], STDERR_FILENO);
		exit_status(": numeric argument required\n", 2, STDERR_FILENO, shell);
	}
}
