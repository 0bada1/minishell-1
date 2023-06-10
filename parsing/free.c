/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalshaer <kalshaer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:35:50 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 16:21:20 by kalshaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_2d_utils(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		if (array[i])
		{
			while (array[i])
			{
				if (array[i] != NULL)
				{
					free(array[i]);
					array[i++] = NULL;
				}
			}
		}
		free(array);
		array = NULL;
	}
}

void	free_2d(char **array)
{
	if (array == NULL)
		return ;
	if (array[0] == NULL)
	{
		free(array);
		array = NULL;
		return ;
	}
	free_2d_utils(array);
}

void	free_3d_utils(char ***array, int i)
{
	int	j;

	j = 0;
	if (array)
	{
		while (array[i])
		{
			j = 0;
			while (array[i][j])
			{
				if (array[i][j] != NULL)
				{
					free(array[i][j]);
					array[i][j++] = NULL;
				}
			}
			free(array[i]);
			array[i++] = NULL;
		}
		free(array);
		array = NULL;
	}
}

void	free_3d(char ***array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (!array[0])
	{
		free(array);
		array = NULL;
		return ;
	}
	if (!array[0][0])
	{
		while (array[i])
			free_2d(array[i++]);
		free(array);
		array = NULL;
		return ;
	}
	free_3d_utils(array, i);
}

void	free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
