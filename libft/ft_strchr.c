/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:29:23 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 19:07:24 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if ((char)c == *s)
		return ((char *)s);
	return (0);
}

/*int	main(void)
{
	char	*test = "bonjour";
	char	chartest = '\0';

	printf("%s\n", ft_strchr(test, chartest));
	printf("%s\n", strchr(test, chartest));
}*/
