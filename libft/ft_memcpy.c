/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:13:20 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/13 18:14:14 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_copied;
	char	*src_copied;

	i = 0;
	if (dst == src || n == 0)
		return (dst);
	dst_copied = (char *)dst;
	src_copied = (char *)src;
	while (i < n)
	{
		dst_copied[i] = src_copied[i];
		i++;
	}
	dst = dst_copied;
	return (dst);
}
