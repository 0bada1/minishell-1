/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:34:05 by ooutabac          #+#    #+#             */
/*   Updated: 2022/05/28 18:43:32 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	int			bzero;
	char		*char_s;

	i = 0;
	bzero = 0;
	char_s = (char *)s;
	while (i < n)
	{
		char_s[i] = bzero;
		i++;
	}
	s = char_s;
	return ;
}
