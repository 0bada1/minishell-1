/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:09:07 by kalshaer          #+#    #+#             */
/*   Updated: 2023/06/04 18:40:27 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	print_position(char **args)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 1;
	while (args[++i])
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			p++;
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] != 'n')
					return (--p);
			}
		}
	}
	return (p);
}

void	check_n_option(char **args, int *n_option, int *i, int *i2)
{
	int	j;

	while (args[*i2])
	{
		if (ft_strncmp(args[*i2], "-n", 2) == 0)
		{
			*n_option = 1;
			j = 0;
			while (args[1][++j])
				if (args[1][j] != 'n')
					*n_option = 0;
		}
		*i2 = *i2 + 1;
	}
	if (*n_option != 0)
		*i = print_position(args);
	while (args[*i])
	{
		ft_putstr_fd(args[*i], 1);
		if (args[*i + 1] && args[*i][0] != '\0')
			write(1, " ", 1);
		*i = *i + 1;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	i2;
	int	n_option;

	i = 1;
	i2 = 1;
	n_option = 0;
	if (nb_args(args) > 1)
		check_n_option(args, &n_option, &i, &i2);
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
