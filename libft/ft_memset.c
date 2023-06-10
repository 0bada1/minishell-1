/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:59:15 by ooutabac          #+#    #+#             */
/*   Updated: 2022/05/31 15:50:35 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*altb;

	altb = b;
	while (len--)
		*altb++ = (unsigned char)c;
	return (b);
}

/*int	main(void)
{
	ft_memset("Hello", 65, -3);
}*/
