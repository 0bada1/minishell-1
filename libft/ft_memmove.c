/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:30:14 by ooutabac          #+#    #+#             */
/*   Updated: 2022/05/28 19:43:48 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_moved;
	char	*src_moved;

	dst_moved = (char *)dst;
	src_moved = (char *)src;
	if (dst == src)
	{
		return (dst);
	}
	if (dst > src)
	{
		while (len--)
		{
			*(dst_moved + len) = *(src_moved + len);
		}
		return (dst);
	}
	else
	{
		while (len--)
		{
			*dst_moved++ = *src_moved++;
		}
		return (dst);
	}
}
