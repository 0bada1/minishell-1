/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:32:41 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/11 13:13:31 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_strdup(char *str);

char	*ft_strdup(char *s1)
{
	char	*strduped;
	size_t	i;
	size_t	s1_length;

	i = 0;
	s1_length = ft_strlen_strdup(s1);
	if (!s1)
		return (NULL);
	strduped = malloc(sizeof(char) * s1_length + 1);
	if (!strduped)
		return (NULL);
	while (i < s1_length)
	{
		strduped[i] = s1[i];
		i++;
	}
	strduped[i] = '\0';
	return (strduped);
}

size_t	ft_strlen_strdup(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*int	main(void)
{
	char	*str = "Hello, this is Obada";
	printf("%s\n", ft_strdup(str));
}*/