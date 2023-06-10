/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:48:08 by ooutabac          #+#    #+#             */
/*   Updated: 2022/06/11 16:49:22 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*t;

	if (*alst)
	{
		t = ft_lstlast(*alst);
		t->next = &*new;
	}
	else
		*alst = new;
}

// int main()
// {
// t_list * l =  NULL; t_list * l2 =  NULL; 
// ft_lstadd_back(&l, ft_lstnew((void*)1));
// ft_lstadd_back(&l, ft_lstnew((void*)2));
// ft_lstadd_back(&l, ft_lstnew((void*)3));
// printf ("%d", (int) l->next->next->content);
// }
