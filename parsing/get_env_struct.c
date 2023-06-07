/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:27:55 by ooutabac          #+#    #+#             */
/*   Updated: 2023/06/07 20:13:23 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_path(t_shell_s *minishell, char **envp)
{
	t_counter	count;
	char		*temp;

	if (!envp || !envp[0])
		return (minishell->path = NULL, minishell);
	count.i = 0;
	count.j = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "PATH=", 5))
		{
			minishell->path = ft_split(envp[count.i - 1] + 5, ':');
			count.j = 0;
			while (minishell->path[count.j])
			{
				temp = minishell->path[count.j];
				minishell->path[count.j++] = ft_strjoin(temp, "/");
				free(temp);
			}
			break ;
		}
		else if (count.i == ft_strstrlen(envp))
			minishell->path = ft_calloc(1, sizeof(char *));
	}
	return (minishell->path[count.j] = NULL, minishell);
}
				// printf("path[%i] = %s\n", count.j, minishell->path[count.j]);

int	ft_strlen_equals(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_shell_s	*get_env_struct_v1(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i])
	{
		count.j = 0;
		minishell->envp->envp[count.i] = ft_strdup(envp[count.i]);
		minishell->envp->key[count.i] = malloc(sizeof(char)
				* ft_strlen_equals(envp[count.i]) + 1);
		while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
		{
			minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
			count.j++;
		}
		minishell->envp->key[count.i][count.j] = '\0';
		minishell->envp->value[count.i] = ft_strchr(envp[count.i], '=') + 1;
		count.i++;
	}
	minishell->envp->envp[count.i] = NULL;
	minishell->envp->key[count.i] = NULL;
	minishell->envp->value[count.i] = NULL;
	return (minishell);
}

t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	if (!envp || !envp[0])
	{
		minishell->envp = ft_calloc(sizeof(t_env_s), 1);
		minishell->envp->envp = ft_calloc(sizeof(char *), 1);
		minishell->envp->key = ft_calloc(sizeof(char *), 1);
		minishell->envp->value = ft_calloc(sizeof(char *), 1);
		return (minishell->envp->env_size = 0, minishell);
	}
	count.i = 0;
	while (envp[count.i])
		count.i++;
	minishell->envp = ft_calloc(sizeof(t_env_s), 1);
	minishell->envp->env_size = count.i;
	minishell->envp->envp = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell->envp->key = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell->envp->value = ft_calloc(sizeof(char *),
			minishell->envp->env_size + 1);
	minishell = get_env_struct_v1(minishell, envp);
	return (minishell->envp->envp[count.i] = NULL, minishell);
}
	// count.i = 0;
	// while (envp[count.i])
	// {
	// 	count.j = 0;
	// 	minishell->envp->envp[count.i] = ft_strdup(envp[count.i]);
	// 	minishell->envp->key[count.i] = malloc(sizeof(char)
	// 			* ft_strlen_equals(envp[count.i]) + 1);
	// 	while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
	// 	{
	// 		minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
	// 		count.j++;
	// 	}
	// 	minishell->envp->key[count.i][count.j] = '\0';
	// 	minishell->envp->value[count.i] = ft_strchr(envp[count.i], '=') + 1;
	// 	count.i++;
	// }
	// minishell->envp->envp[count.i] = NULL;
	// minishell->envp->key[count.i] = NULL;
	// minishell->envp->value[count.i] = NULL;
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
		// minishell->envp->key[count.i][count.j] = envp[count.i][count.j];
		// count.j++;
		// printf("key[%i] = %s\nvalue[%i] = %s\n", count.i,
		// minishell->envp->key[count.i], count.i,
		// minishell->envp->value[count.i]);
	// printf("\n\n\n");
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);

// get_env_struct as linked list
// t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
// {
// 	t_env_s		*temp;
// 	t_counter	count;

// 	if (!minishell)
// 		return (NULL);
// 	if (!envp)
// 		return (minishell);
// 	count.i = 0;
// 	while (envp[count.i])
// 		count.i++;
// 	minishell->envp = ft_calloc(sizeof(t_env_s), 1);
// 	temp = minishell->envp;
// 	// printf("count.i in envp function = %i\n\n", count.i);
// 	count.j = 0;
// 	while (count.j < count.i)
// 	{
// 		count.k = 0;
// 		temp->env_size = count.i;
// 		temp->envp = ft_strdup(envp[count.j]);
// 		temp->key = malloc(sizeof(char) * ft_strlen_equals(envp[count.j]) + 1);
// 		while (envp[count.j][count.k] && envp[count.j][count.k] != '=')
// 		{
// 			temp->key[count.k] = envp[count.j][count.k];
// 			count.k++;
// 		}
// 		temp->key[count.k] = '=';
// 		count.k++;
// 		temp->key[count.k] = '\0';
// 		temp->value = ft_strchr(envp[count.j], '=') + 1;
// 		// printf("envp[%i] = %s\nkey[%i] = %s\nvalue[%i] = %s\n",
//		count.j, temp->envp, count.j, temp->key, count.j, temp->value);
// 		if (count.j + 1 < minishell->envp->env_size)
// 		{
// 			temp->next = ft_calloc(sizeof(t_env_s), 1);
// 			temp = temp->next;
// 		}
// 		else
// 			temp->next = NULL;
// 		count.j++;
// 	}
// 	return (minishell);
// }
