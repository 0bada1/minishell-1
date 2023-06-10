/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:31:48 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 16:47:10 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	i;

	i = 0;
	src_length = ft_strlen(src);
	if (!src)
		return (0);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_length);
}

// int	main(void)
// {
// 	char dest[10];
// 	memset(dest, 'A', 10);
// 	char src[] = "coucou";
// 	printf("%zu\n", ft_strlcpy(dest, src, 2));
// 	printf("%c\n", dest[2]);
// 	printf("%s\n", dest);
// 	printf("%s\n", src);
// //
// 	char tstdest[10];
// 	memset(tstdest, 'A', 10);
// 	char tstsrc[] = "coucou";
// 	printf("%zu\n", strlcpy(tstdest, tstsrc, 2));
// 	printf("%c\n", tdest[2]);
// 	printf("%s\n", tstdest);
// 	printf("%s\n", tstsrc);
// }