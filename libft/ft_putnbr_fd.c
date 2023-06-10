/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:18:52 by ooutabac          #+#    #+#             */
/*   Updated: 2022/05/28 20:38:38 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd_putnbr(char c, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_fd_putnbr('-', fd);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd_putnbr((char)(nbr % 10 + 48), fd);
}

void	ft_putchar_fd_putnbr(char c, int fd)
{
	write(fd, &c, 1);
}

/*int main(void)
{
	int i;

	i = -100;
	while (i != 500)
	{
		ft_putnbr_fd(i, 1);
		i+= 50;
		printf("\n");
	}
	printf("\n");
	ft_putnbr_fd(-2147483648LL, 2);
	printf("\n");
	return 0;
}*/