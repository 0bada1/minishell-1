/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:22:54 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/11 18:56:56 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int main(void)
{
    printf("%s\n", ft_itoa(0));

    return (0);
}*/

static int	countdigt(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	number;
	char			*str;
	size_t			len;

	len = countdigt(n);
	number = n;
	if (n < 0)
	{
		number = -1 * n;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (number == 0)
		str[--len] = '0';
	while (number)
	{
		str[--len] = number % 10 + '0';
		number /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
