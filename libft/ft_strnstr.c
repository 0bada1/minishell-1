/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:44:25 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 19:45:01 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int main(void)
{
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
    printf("%s\n", ft_strnstr(haystack, needle, 10));

    return (0);
}*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*m;

	m = (char *)haystack;
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0' && i + j < len)
			j++;
		if (j == ft_strlen(needle))
			return (&m[i]);
		i++;
	}
	return (NULL);
}
