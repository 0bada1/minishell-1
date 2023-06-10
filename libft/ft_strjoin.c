/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:06:22 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 17:14:30 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	main(void)
{
	char *s1 = "Obada ";
	char *s2 = "is 65 kg.";
	printf("%s", s1);
	printf("%s\n", s2);
	char *strjoined = ft_strjoin(s1, s2);
	printf("%s\n", strjoined);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	size_t		total_len;
	char		*str_joined;

	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str_joined = malloc(sizeof(char) * total_len);
	if (str_joined == NULL)
		return (NULL);
	while (j < ft_strlen(s1))
		str_joined[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		str_joined[i++] = s2[j++];
	str_joined[i] = '\0';
	return (str_joined);
}
