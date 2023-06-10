/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:32:18 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 19:12:33 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	while (i > 0 && *s != (char)c)
	{
		s--;
		i--;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (0);
}

// int main ()
// {
// 	printf("%s", ft_strrchr("hello help", 'e'));
// }